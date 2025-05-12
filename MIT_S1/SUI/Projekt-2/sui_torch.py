import numpy as np

class Tensor:
    def __init__(self, value, back_op=None):
        self.value: int = value
        self.grad: np.array = np.zeros_like(value)
        self.back_op = back_op

    def __str__(self):
        str_val = str(self.value)
        str_val = '\t' + '\n\t'.join(str_val.split('\n'))
        str_bwd = str(self.back_op.__class__.__name__)
        return 'Tensor(\n' + str_val + '\n\tbwd: ' + str_bwd + '\n)'

    @property
    def shape(self):
        return self.value.shape

    def backward(self, deltas=None):
        if deltas is not None:
            assert deltas.shape == self.value.shape, f'Expected gradient with shape {self.value.shape}, got {deltas.shape}'
            self.grad += deltas  # Accumulate gradients
        else:
            if self.shape != tuple() and np.prod(self.shape) != 1:
                raise ValueError(f'Can only backpropagate a scalar, got shape {self.shape}')
            self.grad += np.ones_like(self.value)  # Initialize with ones for scalar

        # Call the backward operation if it exists
        if self.back_op:
            self.back_op.backward(self.grad)

class BackwardOperation:
    def backward(self, upstream_grad):
        raise NotImplementedError('Backward method not implemented for this operation.')

class SumBackward(BackwardOperation):
    def __init__(self, tensor: Tensor):
        self.tensor: Tensor = tensor

    def backward(self, upstream_grad):
        self.tensor.backward(upstream_grad * np.ones_like(self.tensor.value))

def sui_sum(tensor):
    value = np.sum(tensor.value)
    return Tensor(value, back_op=SumBackward(tensor))

class AddBackward(BackwardOperation):
    def __init__(self, a: Tensor, b: Tensor):
        self.a: Tensor = a
        self.b: Tensor = b

    def backward(self, upstream_grad):
        self.a.backward(upstream_grad)
        self.b.backward(upstream_grad)

def add(a, b):
    return Tensor(a.value + b.value, back_op=AddBackward(a, b))

class SubtractBackward(BackwardOperation):
    def __init__(self, a: Tensor, b: Tensor):
        self.a: Tensor = a
        self.b: Tensor = b

    def backward(self, upstream_grad):
        self.a.backward(upstream_grad)
        self.b.backward(-upstream_grad)

def subtract(a, b):
    return Tensor(a.value - b.value, back_op=SubtractBackward(a, b))


class MultiplyBackward(BackwardOperation):
    def __init__(self, a, b):
        self.a: Tensor = a
        self.b: Tensor = b

    def backward(self, upstream_grad):
        self.a.backward(upstream_grad * self.b.value)
        self.b.backward(upstream_grad * self.a.value)

def multiply(a, b):
    return Tensor(a.value * b.value, back_op=MultiplyBackward(a, b))

class ReluBackward(BackwardOperation):
    def __init__(self, tensor: Tensor):
        self.tensor: Tensor = tensor

    def backward(self, upstream_grad):
        self.tensor.backward(upstream_grad * (self.tensor.value > 0))


def relu(tensor):
    return Tensor(np.maximum(tensor.value, 0), back_op=ReluBackward(tensor))

class DotProductBackward(BackwardOperation):
    def __init__(self, a: Tensor, b: Tensor):
        self.a: Tensor = a
        self.b: Tensor = b

    def backward(self, upstream_grad):
        grad_a = np.dot(upstream_grad, self.b.value.T)
        self.a.backward(grad_a)

        grad_b = np.dot(self.a.value.T, upstream_grad)
        self.b.backward(grad_b)

def dot_product(a, b):
    value = np.dot(a.value, b.value)
    return Tensor(value, back_op=DotProductBackward(a, b))
