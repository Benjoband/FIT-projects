@include('header')

<title>Přihlášení</title>

<form method="POST" action="/uzivatel/autentifikace" enctype="multipart/form-data">
    @csrf
    <div class="form-container">
    <table class="create-table">
        <tr>
            <th class="create-table-header" colspan="2">Přihlášení</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Email</td>
            <td class="create-table-td"><input type="email" name="email" class="input-field" placeholder="Email" value="{{old('email')}}">
            @error('email')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
        <tr>
            <td class="create-table-td-legend">Heslo</td>
            <td class="create-table-td"><input type="password" name="password" class="input-field" placeholder="Heslo" >
            @error('password')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
    </table>
    <input type="submit" value="Přihlásit se" class="create-submit">
    </div>
    <table class="already-acc-table">
        <tr>
            <th class="already-acc-text" colspan="2">Ještě nemáte účet?</th>
        </tr>
        <tr>
            <td onclick="window.location='/uzivatel/registrace'" class="already-acc-button">Registrovat se</td>
        </tr>
    </table>
</form>


@include('footer')