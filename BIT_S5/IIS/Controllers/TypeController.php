<?php

namespace App\Http\Controllers;

use App\Models\Type;
use App\Models\Parameter;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;

class TypeController extends Controller
{
    public function create()
    {
        return view('type.vytvorit_typ',
            [
                'params' => Parameter::all(),
            ]
        );
    }

    public function store(Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'description' => 'nullable',
        ]);

        $newType = Type::create($formContent);

        foreach($request->input('parameter') as $parameter) {
            $newType->parameter()->attach($parameter);
        }

        return redirect('/')->with('success', 'Typ byl úspěšně vytvořen.');
    }
}
