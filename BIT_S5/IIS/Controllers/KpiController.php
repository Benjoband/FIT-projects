<?php

namespace App\Http\Controllers;

use App\Models\Kpi;
use App\Models\Type;
use App\Models\Device;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;

class KpiController extends Controller
{
    public function create()
    {
        $systems = auth()->user()->system;

        $devices = collect();
        if ($systems->count() > 0) {
            foreach ($systems as $system) {
                $devices = $devices->merge($system->device);
            }
        }
        $saveParam = collect();

        if ($devices->count() > 0) {
            foreach ($devices as $device) {
                $paramDevice = $device->type->parameter;
                $saveParam = $saveParam->merge($paramDevice);
            }
        }

        $saveParam = $saveParam->unique('id');

        return view('kpi.vytvorit_kpi', [
            'devices' => $devices,
            'params'  => $saveParam,
        ]);
    }

    public function store()
    {
        $formContent = request()->validate([
            'name' => 'required',
            'operator' => 'required',
            'value' => 'required',
            'device_id' => 'required',
            'parameter_id' => 'required',
        ]);

        $device_id = $formContent['device_id'];
        $parameter_id = $formContent['parameter_id'];

        $device = Device::find($device_id);
        $system = $device->system;

        if(!$this->checkPar())
        {
            return redirect('/moje-systemy/' .$system->id)->with('error', 'Parametr nebyl nalezen.');
        }
        
        $value = 0;
        if($device)
        {
            $pivotRow = $device->parameter()->where('parameter_id', $parameter_id)->first();
        
            if ($pivotRow) {
                $value = $pivotRow->pivot->value;
            } else {
                return redirect('/moje-systemy/' .$system->id)->with('error', 'Parametr nebyl nalezen.');
            }
        }else
        {
            return redirect('/moje-systemy/' .$system->id)->with('error', 'Parametr nebyl nalezen.');
        }

        $status = $this->checkKpi(floatval($value), floatval($formContent['value']), $formContent['operator']);
        $formContent['status'] = $status;

        Kpi::create($formContent);

        return redirect('/moje-systemy/' .$system->id)->with('success', 'KPI bylo úspěšně vytvořeno.');
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

    private function checkPar()
    {
        $device_id = request()->device_id;
        $parameter_id = request()->parameter_id;

        $device = Device::find($device_id);

        if($device)
        {
            $type = $device->type;
        
            if($type)
            {
                $parameters = $type->parameter;
                $hasParameter = $parameters->contains('id', $parameter_id);
        
                if($hasParameter) 
                {
                    return true;
                }
            }
        }
        return false;
    }

    public function delete()
    {
        $id = request()->id;
        $kpi = Kpi::find($id);
        $system = $kpi->device->system;
        $kpi->delete();

        return redirect('/moje-systemy/' .$system->id)->with('success', 'KPI bylo úspěšně smazáno.');
    }

    public function edit(Kpi $kpi)
    {

        return view('kpi.editace_kpi', [
            'device' => $kpi->device,
            'param'  => $kpi->parameter,
            'kpi' => $kpi,
        ]);
    }

    public function update(Kpi $kpi)
    {   
        $formContent = request()->validate([
            'name' => 'required',
            'operator' => 'required',
            'value' => 'required',
        ]);

        $device_id = $kpi->device->id;
        $parameter_id = $kpi->parameter->id;

        $device = Device::find($device_id);
        $system = $device->system;
        
        $value = 0;
        if($device)
        {
            $pivotRow = $device->parameter()->where('parameter_id', $parameter_id)->first();
        
            if ($pivotRow) {
                $value = $pivotRow->pivot->value;
            } else {
                return redirect('/moje-systemy/' .$system->id)->with('error', 'Parametr nebyl nalezen.');
            }
        }else
        {
            return redirect('/moje-systemy/' .$system->id)->with('error', 'Parametr nebyl nalezen.');
        }

        $status = $this->checkKpi(floatval($value), floatval($formContent['value']), $formContent['operator']);
        $formContent['status'] = $status;

        $kpi->update($formContent);

        return redirect('/moje-systemy/' .$system->id)->with('success', 'KPI bylo úspěšně upraveno.');
    }

}
