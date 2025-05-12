@include('header')
<title>Moje systémy</title>

@unless(count($systems) == 0)

<table class="my-systems-table">
  <tr>
      <th class="my-systems-table-header" colspan="3">Moje systémy</th>
  </tr>

  @foreach($systems as $system)
      <tr>
        <td class="my-systems-table-td" onclick="window.location='/moje-systemy/{{$system->id}}';" style="cursor:pointer;">
              {{$system->name}}
        </td>
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
        @else
        <td class="my-systems-table-td-link">&nbsp;</td>
        <td class="my-systems-table-td-link">&nbsp;</td>
        @endif
      </tr>
  @endforeach
  <tr>
      <td class="table-add" colspan="3" onclick="window.location='vytvorit-system'">Přidat systém</td>
  </tr>
</table>

@else
<table class="my-systems-table">
  <tr>
      <th class="systems-table-header">Žádný systém nenalezen</th>
  </tr>
</table>
@endunless

@include('footer')

