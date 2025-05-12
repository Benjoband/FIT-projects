@include('header')
<title>Procházet systémy</title>

<form action="/prochazet-systemy">
  <div class="search-container">
      <input type="text" placeholder="Hledat systém" name="search" class="search-input">
      <button type="submit" class="search-button">Hledat</button>
  </div>
</form>

@unless(count($systems) == 0)

<table class="systems-table">
  <tr>
      <th class="systems-table-header" colspan="5">Všechny systémy</th>
  </tr>
  <tr>
    <td class="systems-table-legend">Název</td>
    <td class="systems-table-legend">Lokace</td>
    <td class="systems-table-legend">Popis</td>
  </tr>

  @foreach($systems as $system)
      <tr>
        <td class="systems-table-td">
              {{$system->name}}
        </td>
        <td class="systems-table-td">
            {{$system->location}}
        </td>
        <td class="systems-table-td">
          {{$system->description}}
        </td>
        @auth
        @if($loggedUser->id == $system->user_id || $loggedUser->role_id == 1)
        <td class="my-systems-table-td-link" onclick="window.location='/moje-systemy/{{$system->id}}/editace-systemu'">
            Upravit
        </td>
        <form method="POST" action="/moje-systemy/{{$system->id}}/smazat-system">
            @csrf
            @method('DELETE')
            <td class="my-systems-table-td-link">
                <input type="submit" value="Smazat" class="my-systems-table-delete">
            </td>
        </form>
        @endif
        @endauth
      </tr>
  @endforeach
</table>
@else
<table class="systems-table">
  <tr>
      <th class="systems-table-header">Žádný systém nenalezen</th>
  </tr>
</table>
@endunless

@include('footer')

