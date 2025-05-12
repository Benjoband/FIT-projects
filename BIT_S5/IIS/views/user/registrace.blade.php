@include('header')

<title>Registrace</title>

<form method="POST" action="/uzivatel" enctype="multipart/form-data">
    @csrf
    <div class="form-container">
    <table class="create-table">
        <tr>
            <th class="create-table-header" colspan="2">Registrace</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Jméno</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Jméno" value="{{old('name')}}">
            @error('name')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
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
        <tr>
            <td class="create-table-td-legend">Potvrzení hesla</td>
            <td class="create-table-td"><input type="password" name="password_confirmation" class="input-field" placeholder="Potvrzení hesla" >
            @error('confirmation_password')
                <div class="alert alert-danger">{{ $message }}</div>
            @enderror
            </td>
        </tr>
    </table>
    <input type="submit" value="Registrovat" class="create-submit">
    </div>
    <table class="already-acc-table">
        <tr>
            <th class="already-acc-text" colspan="2">Již máte účet?</th>
        </tr>
        <tr>
            <td onclick="window.location='/uzivatel/prihlaseni'" class="already-acc-button">Přihlásit se</td>
        </tr>
    </table>
</form>

@include('footer')