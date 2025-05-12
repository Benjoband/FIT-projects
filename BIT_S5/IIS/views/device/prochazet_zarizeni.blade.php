@include('header')
<title>Procházet zařízení</title>

<form action="/prochazet-zarizeni">
  <div class="search-container">
      <input type="text" placeholder="Hledat zařízení" name="search" class="search-input">
      <button type="submit" class="search-button">Hledat</button>
  </div>
</form>

@unless(count($devices) == 0)

<table class="devices-table">
  <tr id="headerRow">
    <td class="devices-table-header" colspan="3">Zařízení</td>
  </tr>
  <tr>
    <td class="devices-legend">Název</td>
    <td class="devices-legend">Lokace</td>
    <td class="devices-legend">Typ</td>
  </tr>
  @foreach($devices as $device)
    <tr class="toggle-row" onclick="toggleKPIs(this)">
      <td class="devices-table-td">{{$device->name}}</td>
      <td class="devices-table-td">{{$device->location}}</td>
      <td class="devices-table-td">{{$device->type->name}}</td>
    </tr>
    <?php $params0 = $device->type->parameter; 
          $paramsWithValue = $device->parameter; 
          $params = collect();
          foreach($params0 as $param0)
          {
            $pushed = false;
            foreach($paramsWithValue as $paramWithValue)
            {
              if($param0->id == $paramWithValue->id)
              {
                $params->push($paramWithValue);
                $pushed = true;
              }
            }
            if(!$pushed)
            {
              $params->push($param0);
            }
          }
          
          ?>
    
    @foreach($params as $param)
      <tr class="kpi-row" style="display: none;">
          <td class="devices-table-param-name">{{$param->name}}</td>
          <td class="devices-table-param-val">{{$param->pivot->value}} {{$param->unit}}</td>
          <td class="devices-table-td-link" onclick="window.location='/editace-hodnot/{{$device->id}}/{{$param->id}}'">Upravit</td>
      </tr>
    @endforeach
  @endforeach
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
    <th class="devices-table-header">Žádné zařízení nepřidáno</th>
  </tr>
</table>

@endunless

@include('footer')

