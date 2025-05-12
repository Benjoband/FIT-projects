@include('header')
<title>Vytvořit systém</title>



<form method="POST" action="/vytvorit-system/vytvareni" enctype="multipart/form-data">
    @csrf
    <div class="form-container">
    <table class="create-table">
        <tr>
            <th class="create-table-header" colspan="2">Vytvořit systém</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Název</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název systému" value="{{old('name')}}">
            @error('name')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Lokace</td>
            <td class="create-table-td"><input type="text" name="location" class="input-field" placeholder="Lokace systému" value="{{old('location')}}"></td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Popis</td>
            <td class="create-table-td"><input type="text" name="description" class="input-field" placeholder="Popis systému" value="{{old('description')}}"></td>
        </tr>
    </table>
    <input type="submit" value="Vytvořit" class="create-submit">
    </div>
</form>



@include('footer') 