@include('header')
<title>Vytvořit parametr</title>

<form method="POST" action="/vytvorit-parametr/vytvareni" enctype="multipart/form-data" id="create-form">
    @csrf
  <div class="form-container">
    <table class="create-table" id="type-table">
        <tr>
            <th class="create-table-header" colspan="3">Vytvořit parametr</th>
        </tr>
        <tr>
            <td class="create-table-td-legend">Jméno</td>
            <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Jméno" required></td>
          </tr>
        <tr>
            <td class="create-table-td-legend">Jednotka</td>
            <td class="create-table-td"><input type="text" name="unit" class="input-field" placeholder="Jednotka"></td>
          </tr>
        </tr>
    </table>
    <input type="submit" value="Vytvořit" class="create-submit">
  </div>
</form>

@include('footer')
