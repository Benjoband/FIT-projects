@include('header')
<title>Vytvořit zařízení</title>

<form method="POST" action="/vytvorit-zarizeni/vytvareni" enctype="multipart/form-data">
    @csrf
    <div class="form-container">
        <table class="create-table">
            <tr>
                <th class="create-table-header" colspan="2">Vytvořit zařízení</th>
            </tr>
            <tr>
                <td class="create-table-td-legend">Název</td>
                <td class="create-table-td"><input type="text" name="name" class="input-field" placeholder="Název zařízení" value="{{old('name')}}">
                @error('name')
                    <div class="alert alert-danger">{{ $message }}</div>
                @enderror
                </td>
            </tr>
            <tr>
                <td class="create-table-td-legend">Lokace</td>
                <td class="create-table-td"><input type="text" name="location" class="input-field" placeholder="Lokace zařízení" value="{{old('location')}}"></td>
            </tr>
            <tr>
                <td class="create-table-td-legend">Popis</td>
                <td class="create-table-td"><input type="text" name="description" class="input-field" placeholder="Popis zařízení" value="{{old('description')}}"></td>
            </tr>
            <tr>
                <td class="create-table-td-legend">Typ</td>
                <td class="create-table-td"><select id="select" class="select" name="type_id">
                    @foreach($types as $type)
                        <option value="{{$type->id}}">{{$type->name}}</option>
                    @endforeach
                </select></td>
            </tr>
            <tr>
                <td class="create-table-td-legend">Systém</td>
                <td class="create-table-td"><select id="select" class="select"  name="system_id">
                @if($systemChoose != NULL)
                    <option value="{{$systemChoose->id}}">{{$systemChoose->name}}</option>
                @endif
                @foreach($systems as $system)
                    @if($systemChoose != NULL)
                        @if($system->id != $systemChoose->id)
                            <option value="{{$system->id}}">{{$system->name}}</option>
                        @endif
                    @else
                        <option value="{{$system->id}}">{{$system->name}}</option>
                    @endif
                @endforeach
                </select></td>
            </tr>
        </table>
        <input type="submit" value="Vytvořit" class="create-submit">
    </div>
</form>


@include('footer')