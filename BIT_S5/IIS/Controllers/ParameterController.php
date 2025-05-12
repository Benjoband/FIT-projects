<?php

namespace App\Http\Controllers;

use App\Models\Parameter;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;

class ParameterController extends Controller
{
    public function create()
    {
        return view('vytvorit-parametr');
    }

    public function store(Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'unit' => 'required',
        ]);

        Parameter::create($formContent);
        
        return redirect('/')->with('success', 'Parametr byl úspěšně vytvořen.');
    }
}
