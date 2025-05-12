<?php

namespace App\Http\Controllers;

use App\Models\Kpi;
use App\Models\Type;
use App\Models\Device;
use App\Models\System;
use App\Models\Parameter;
use Illuminate\Http\Request;
use Illuminate\Validation\Rule;
use App\Http\Controllers\Controller;

class DeviceController extends Controller
{
    public function create()
    {
        return view('device.vytvorit_zarizeni', [
            'types' => Type::all(),
            'systems' => auth()->user()->system,
            'systemChoose' => null,
        ]);
    }

    public function createInSystem(System $system)
    {
        return view('device.vytvorit_zarizeni', [
            'types' => Type::all(),
            'systems' => auth()->user()->system,
            'systemChoose' => $system,
        ]);
    }

    public function store(Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'description' => 'nullable',
            'location' => 'nullable',
            'type_id' => 'required',
            'system_id' => 'required',
        ]);

        Device::create($formContent);
        $system = System::find($formContent['system_id']);
        $systemId = $system->id;
        
        return redirect('/moje-systemy/' . $systemId)->with('success', 'Zařízení bylo úspěšně vytvořeno.');
    }

    public function delete(Device $device)
    {
        $system = $device->system;
        $systemId = $system->id;
        $device->delete();

        return redirect('/moje-systemy/' . $systemId)->with('success', 'Zařízení bylo úspěšně smazáno.');
    }

    public function edit(Device $device)
    {

        return view('device.editace_zarizeni', [
            'device' => $device,
            'types' => Type::all(),
            'systems' => auth()->user()->system,
            'systemChoose' => $device->system,
            'typeChoose' => $device->type,
        ]);
    }

    public function update(Device $device, Request $request)
    {

        $formContent = $request->validate([
            'name' => 'required',
            'description' => 'nullable',
            'location' => 'nullable',
            'type_id' => 'required',
            'system_id' => 'required',
        ]);

        $device->update($formContent);

        return back()->with('success', 'Zařízení bylo úspěšně upraveno.');
    }

    public function deviceFind()
    {
        return view('device.prochazet_zarizeni', [
            'devices' => Device::latest()->filter(request(['search']))->get(),
        ]);
    }

    public function editValues(Device $device, Parameter $parameter)
    {
        if($device->parameter->contains($parameter->id)) {
            $pivot = $device->parameter->find($parameter->id)->pivot;
            $value = $pivot ? $pivot->value : null;
        }
        else
        {
            $value = null;
        }


        return view('device.editace_hodnot', [
            'device' => $device,
            'param' => $parameter,
            'value' => $value,
        ]);
    }

    public function updateValues(Device $device, Parameter $parameter, Request $request)
    {
        $formContent = $request->validate([
            'value' => 'required',
        ]);

        $device->parameter()->sync([$parameter->id => ['value' => $formContent['value']]]);

        $kpi = Kpi::where('device_id', $device->id)->where('parameter_id', $parameter->id)->first();
        
        $status = $this->checkKpi(floatval($formContent['value']), floatval($kpi->value), $kpi->operator);
        $formContent['status'] = $status;

        $kpi->update($formContent);

        return redirect('/prochazet-zarizeni')->with('success', 'Hodnota byla úspěšně upravena.');
    }

    private function checkKpi(float $valueLeft,float $valueRight, string $operator)
    {
        switch($operator)
        {
            case '<':   
                if($valueLeft < $valueRight)
                {
                    return true;
                }
                break;
            case '<=':
                if($valueLeft <= $valueRight)
                {
                    return true;
                }
                break;
            case '>':
                if($valueLeft > $valueRight)
                {
                    return true;
                }
                break;
            case '>=':
                if($valueLeft >= $valueRight)
                {
                    return true;
                }
                break;
            case '=':
                if($valueLeft == $valueRight)
                {
                    return true;
                }
                break;
            case '!=':
                if($valueLeft != $valueRight)
                {
                    return true;
                }
                break;
            default:
                return false;
        }
        return false;
    }
}
