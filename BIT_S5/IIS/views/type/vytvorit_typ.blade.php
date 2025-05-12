@include('header')
<title>Vytvořit typ</title>

<form method="POST" action="/vytvorit-typ/vytvareni" enctype="multipart/form-data" id="create-form">
@csrf
  <div class="form-container">
    <table class="create-table" id="type-table">
        <tr>
            <th class="create-table-header" colspan="3">Vytvořit typ</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Název</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název typu" value="{{old('name')}}">
            @error('name')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
            <td class="create-table-remove-td">&nbsp;</td>
          </tr>
        <tr>
            <td class="create-table-td-legend">Popis</td>
            <td class="create-table-td"><input type="text" name="description" class="input-field" placeholder="Popis typu" value="{{old('description')}}"></td>
            <td class="create-table-remove-td">&nbsp;</td>
          </tr>
        <tr class="type-row">
            <td class="create-table-td-legend">Veličina</td>
            <td class="create-table-td">
                <select class="select" name="parameter[]">
                    @foreach($params as $param)
                        <option value="{{$param->id}}">{{$param->name}}</option>
                    @endforeach
                </select>
            </td>
            <td class="create-table-remove-td">&nbsp;</td>
        </tr>
    </table>
    <button type="button" id="add-row" class="add-param">Přidat parametr</button>
    <input type="submit" value="Vytvořit" class="create-submit">
  </div>
</form>

<script>
    document.addEventListener('DOMContentLoaded', function() {
        // Add Row button functionality
        document.getElementById('add-row').addEventListener('click', function() {
            var table = document.getElementById('type-table');
            var newRow = table.insertRow(table.rows.length);

            newRow.className = 'type-row';

            var cell1 = newRow.insertCell(0);
            var cell2 = newRow.insertCell(1);
            var cell3 = newRow.insertCell(2);

            cell1.className = 'create-table-td-legend';
            cell2.className = 'create-table-td';
            cell3.className = 'create-table-remove-button-type';

            cell1.innerHTML = 'Veličina';
            cell2.innerHTML = '<select class="select" name="parameter[]">@foreach($params as $param)<option value="{{$param->id}}">{{$param->name}}</option>@endforeach</select>';
            cell3.innerHTML = '<button type="button" class="create-table-remove-button">Remove</button>';

            // Remove Row button functionality
            cell3.addEventListener('click', function() {
                table.deleteRow(newRow.rowIndex);
            });
        });
    });
</script>

@include('footer')
