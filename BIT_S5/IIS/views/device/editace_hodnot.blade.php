@include('header')
<title>Editace hodnot</title>

<form method="POST" action="/editace-hodnot/{{$device->id}}/{{$param->id}}/uprava" enctype="multipart/form-data">
    @method('PUT')
    @csrf
    <div class="form-container">
        <table class="create-table">
            <tr>
                <th class="create-table-header" colspan="2">Editace hodnot - {{$device->name}} - {{$param->name}}</th>
            </tr>
            <tr>
                <td class="create-table-td-legend">Hodnota</td>
                <td class="create-table-td"><input type="text" name="value" class="input-field" placeholder="Hodnota" value="{{$value}}">
                @error('value')
                    <div class="alert alert-danger">{{ $message }}</div>
                @enderror
                </td>
            </tr>
            <tr>
                <td class="create-table-td-legend">Jednotka</td>
                <td class="create-table-td"><input type="text" name="unit" class="input-field" placeholder="" value="{{$param->unit}}" readonly></td>
            </tr>
        </table>
        <input type="submit" value="Upravit" class="create-submit">
    </div>
</form>


@include('footer')