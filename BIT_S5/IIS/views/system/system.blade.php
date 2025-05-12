@include('header')

<title>{{$system->name}}</title>

<table class="system-table">
  <tr>
    <th class="system-table-header" colspan="2">{{$system->name}}</th>
  </tr>
  @if($system->location != NULL)
  <tr>
    <td class="system-info-legend">Lokace</td>
    <td class="system-info-td">{{$system->location}}</td>
  </tr>
  @endif
  @if($system->description != NULL)
  <tr>
    <td class="system-info-legend">Popis</td>
    <td class="system-info-td">{{$system->description}}</td>
  </tr>
  @endif
  <tr>
    <td class="system-info-legend">Správce systému</td>
    <td class="system-info-td">{{$admin->name}}</td>
  </tr>
  @if($system->user->count() > 1)
  <tr>
    <td class="system-info-legend">Viditelné pro uživatele:</td>
    @foreach($system->user as $user)
      @if($user->id != $admin->id)
          <td class="system-info-td">{{$user->name}}</td>
        </tr>
        @if(!$loop->last)
          <tr>
            <td class="system-info-td">&nbsp;</td>
        @endif
      @endif
    @endforeach
  @endif
  @if($loggedUser->id == $admin->id || $loggedUser->role_id == 1)
  <tr>
    <td class="table-add" colspan="2" onclick="window.location='/moje-systemy/{{$system->id}}/pridat-uzivatele'">Přidat uživatele
    </td>
  </tr>
  @endif
</table>
@unless(count($devices) == 0)

<table class="system-devices-table">
  <tr id="headerRow">
    <td class="system-devices-table-header" colspan="5">Zařízení</td>
  </tr>
  @foreach($devices as $device)
    <tr class="toggle-row" onclick="toggleKPIs(this)">
      <td class="system-devices-table-td">{{$device->name}}</td>
      <td class="system-devices-table-td">{{$device->location}}</td>
      <td class="system-devices-table-td">{{$device->type->name}}</td>
      @if($loggedUser->id == $admin->id || $loggedUser->role_id == 1)
      <td class="system-devices-table-td-link" onclick="window.location='/editace-zarizeni/{{$device->id}}'">Upravit</td>
      <form method="POST" action="/smazat-zarizeni/{{$device->id}}">
        @csrf
        @method('DELETE')
        <td class="my-systems-table-td-link">
            <input type="submit" value="Smazat" class="my-systems-table-delete">
        </td>
      </form>
      @else
      <td class="system-devices-table-td-link">&nbsp;</td>
      <td class="system-devices-table-td-link">&nbsp;</td>
      @endif
    </tr>
    <?php $params = $device->parameter; ?>
    @foreach($params as $param)
      <tr class="kpi-row" style="display: none;">
          <td class="system-devices-table-param-name">{{$param->name}}</td>
          <td class="system-devices-table-param-val">{{$param->pivot->value}} {{$param->unit}}</td>
          <td class="system-devices-table-kpi">&nbsp;</td>
          <td class="system-devices-table-kpi">&nbsp;</td>
          <td class="system-devices-table-kpi">&nbsp;</td>
      </tr>
    @endforeach
    @if($device->kpi->count() == 0)
      <tr class="kpi-row" style="display: none">
        <td colspan="5" class="system-devices-table-kpi">Žádné KPI</td>
      </tr>
    @else
      <tr class="kpi-row" style="display: none">
        <td class="system-devices-table-kpi-header">KPI</td>
        <td class="system-devices-table-kpi-header">Status</td>
        <td class="system-devices-table-kpi-header">Popis</td>
        <td class="system-devices-table-kpi-header">&nbsp;</td>
        <td class="system-devices-table-kpi-header">&nbsp;</td>
      </tr>
    @endif
    @foreach($device->kpi as $kpi)
      <tr class="kpi-row" style="display: none;">
          <td class="system-devices-table-kpi">{{$kpi->name}}</td>
          @if($kpi->status == False)
            <td class="system-devices-table-kpi" style="color: red;">{{$kpi->status}}</td>
            <td class="system-devices-table-kpi" style="color: red;">Chyba se zařízením</td>
          @else
            <td class="system-devices-table-kpi" style="color: green;">{{$kpi->status}}</td>
            <td class="system-devices-table-kpi" style="color: green;">OK</td>
          @endif
          @if($loggedUser->id == $admin->id || $loggedUser->role_id == 1)
            <td class="system-devices-table-kpi-link" onclick="window.location='/editace-kpi/{{$kpi->id}}'">Upravit</td>
            <form method="POST" action="/smazat-kpi/mazu">
            @csrf
            @method('DELETE')
            <td class="system-devices-table-kpi">
                    <input type="hidden" value="{{$kpi->id}}" name="id" >
                <input type="submit" value="Smazat" class="system-devices-table-kpi-delete">
            </td>
          </form>
          @else
            <td class="system-devices-table-kpi-link">&nbsp;</td>
            <td class="system-devices-table-kpi-link">&nbsp;</td>
          @endif


      </tr>
    @endforeach
  @endforeach
  @if($loggedUser->id == $admin->id || $loggedUser->role_id == 1)
  <tr>
    <td class="table-add" colspan="5" onclick="window.location='/vytvorit-zarizeni/{{$system->id}}'">Přidat zařízení</td>
  </tr>
  @endif
</table>

<script>
  function toggleKPIs(row) {
    var nextRows = getAllNextKPIRows(row);
    nextRows.forEach(function(nextRow) {
      nextRow.style.display = (nextRow.style.display === 'none') ? '' : 'none';
    });
  }

  function getAllNextKPIRows(row) {
    var nextRows = [];
    var nextRow = row.nextElementSibling;
    
    while (nextRow && nextRow.classList.contains('kpi-row')) {
      nextRows.push(nextRow);
      nextRow = nextRow.nextElementSibling;
    }

    return nextRows;
  }
</script>


@else

<table class="system-devices-table">
  <tr>
    <th class="system-devices-table-header">Žádné zařízení nepřidáno</th>
  </tr>
</table>

@endunless

@include('footer')