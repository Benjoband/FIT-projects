@include('header')
<title>Přidání uživatele</title>



<form method="POST" action="/moje-systemy/{{$system->id}}/pridat-uzivatele/pridani" enctype="multipart/form-data">
    @csrf
    <div class="form-container">
    <table class="create-table">
        <tr>
            <th class="create-table-header" colspan="2">Přidání uživatele do systému {{$system->name}}</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Email</td>
            <td class="create-table-td"><input type="email" name="email" class="input-field" placeholder="Email uživatele" value="{{old('name')}}">
            @error('email')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
    </table>
    <input type="submit" value="Přidat uživatele" class="create-submit">
    </div>
</form>



@include('footer') 