@include('header')
<title>Vytvořit KPI</title>

<form method="POST" action="/vytvorit-kpi/vytvareni" enctype="multipart/form-data" id="create-form">
    @csrf
  <div class="form-container">
    <table class="create-table" id="type-table">
        <tr>
            <th class="create-table-header" colspan="2">Vytvořit KPI</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Název</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název kpi" value="{{old('name')}}">
            @error('name')
                <p class="error-message">{{ $message }}</p>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Operátor</td>
            <td class="create-table-td">
                <select name="operator" class="select" required>
                    <option value="=">=</option>
                    <option value=">">></option>
                    <option value="<"><</option>
                    <option valie=">=">>=</option>
                    <option value="<="><=</option>
                    <option value="!=">!=</option>
                </select>
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Hodnota</td>
            <td class="create-table-td"><input type="text" name="value" class="input-field" placeholder="Hodnota" value="{{old('value')}}">
            @error('value')
                <p class="error-message">{{ $message }}</p>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Zařízení</td>
            <td class="create-table-td">
                <select id="select" class="select"  name="device_id" required>
                    @foreach($devices as $device)
                        <option value="{{$device->id}}">{{$device->name}}</option>
                    @endforeach
                </select>
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Parametr</td>        
            <td class="create-table-td">
                <select id="select" class="select" name="parameter_id" required>
                        @foreach($params as $param)
                            <option value="{{$param->id}}">{{$param->name}}</option>
                        @endforeach
                </select>
            </td>
        </tr>
    </table>
    <input type="submit" value="Vytvořit" class="create-submit">
  </div>
</form>

@include('footer')
