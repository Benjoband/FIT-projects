@include('header')
<title>Editace KPI</title>

<form method="POST" action="/editace-kpi/{{$kpi->id}}/uprava" enctype="multipart/form-data" id="create-form">
    @method('PUT')
    @csrf
  <div class="form-container">
    <table class="create-table" id="type-table">
        <tr>
            <th class="create-table-header" colspan="2">Editace KPI</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Název</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název kpi" value="{{$kpi->name}}">
            @error('name')
                <p class="error-message">{{ $message }}</p>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Operátor</td>
            <td class="create-table-td">
                <select name="operator" class="select"  required>
                    <option value="=" {{ $kpi->operator === '=' ? 'selected' : '' }}>=</option>
                    <option value=">" {{ $kpi->operator === '>' ? 'selected' : '' }}> ></option>
                    <option value="<" {{ $kpi->operator === '<' ? 'selected' : '' }}><</option>
                    <option valie=">=" {{ $kpi->operator === '>=' ? 'selected' : '' }}>>=</option>
                    <option value="<=" {{ $kpi->operator === '<=' ? 'selected' : '' }}><=</option>
                    <option value="!=" {{ $kpi->operator === '!=' ? 'selected' : '' }}>!=</option>
                </select>
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Hodnota</td>
            <td class="create-table-td"><input type="text" name="value" class="input-field" placeholder="Hodnota" value="{{$kpi->value}}">
            @error('value')
                <p class="error-message">{{ $message }}</p>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Zařízení</td>
            <td class="create-table-td">
            <input type="text" name="device_id" class="input-field" placeholder="Hodnota" value="{{$device->name}}" readonly>
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Parametr</td>        
            <td class="create-table-td">
                <input type="text" name="param_id" class="input-field" placeholder="Hodnota" value="{{$param->name}}" readonly>
            </td>
        </tr>
    </table>
    <input type="submit" value="Editovat" class="create-submit">
  </div>
</form>

@include('footer')
