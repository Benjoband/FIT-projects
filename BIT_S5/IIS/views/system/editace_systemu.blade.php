@include('header')
<title>Editovat Systém</title>

<form method="POST" action="/moje-systemy/{{$system->id}}/editace-systemu/uprava" enctype="multipart/form-data">
    @csrf
    @method('PUT')
    <div class="form-container">
    <table class="create-table">
        <tr>
            <th class="create-table-header" colspan="2">Editace systému - {{$system->name}}</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Název</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název systému" value="{{$system->name}}">
            @error('name')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Lokace</td>
            <td class="create-table-td"><input type="text" name="location" class="input-field" placeholder="Lokace systému" value="{{$system->location}}"></td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Popis</td>
            <td class="create-table-td"><input type="text" name="description" class="input-field" placeholder="Popis systému" value="{{$system->description}}"></td>
        </tr>
    </table>
    <input type="submit" value="Editovat" class="create-submit">
    </div>
</form>



@include('footer') 