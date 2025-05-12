<?php

namespace App\Http\Controllers;

use App\Models\User;
use App\Models\Device;
use App\Models\System;
use Illuminate\Http\Request;
use Illuminate\Validation\Rule;
use Illuminate\Support\Facades\DB;
use App\Http\Controllers\Controller;
use Illuminate\Contracts\Session\Session;

class SystemController extends Controller
{
    public function systemFind()
    {
        return view('system.prochazet_systemy', [
            'systems' => System::latest()->filter(request(['search']))->get(),
            'loggedUser' => auth()->user(),
        ]);
    }

    public function systemAll()
    {
        $systems = auth()->user()->system;
        return view('system.moje_systemy', [
            'systems' => $systems,
            'loggedUser' => auth()->user(),
        ]);
    }

    public function systemOne(System $system)
    {
        $adminUser = $system->user()->wherePivot('is_admin', true)->first();

        return view('system.system', [
            'system' => $system,
            'devices' => $system->device,
            'admin' => $adminUser,
            'loggedUser' => auth()->user(),
        ]);
    }

    public function create()
    {
        return view('system.vytvorit_system');
    }

    public function store(Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'description' => 'nullable',
            'location' => 'nullable',
        ]);

        $newSystem = System::create($formContent);

        $newSystem->user()->attach(auth()->user(), ['is_admin' => true]);

        return redirect('/')->with('success', 'Systém byl úspěšně vytvořen.');
    }

    public function edit(System $system)
    {
        return view('system.editace_systemu', [
            'system' => $system,
        ]);
    }

    public function update(System $system, Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'description' => 'nullable',
            'location' => 'nullable',
        ]);

        $system->update($formContent);

        return back()->with('success', 'Systém byl úspěšně upraven.');
    }

    public function delete(System $system)
    {
        $system->delete();

        return redirect('/')->with('success', 'Systém byl úspěšně smazán.');
    }

    public function addUser(System $system)
    {
        return view('system.pridat_uzivatele', [
            'system' => $system,
        ]);
    }

    public function storeUser(System $system, Request $request)
    {
        $formContent = $request->validate([
            'email' => 'required|email',
        ]);


        $user = User::where('email', $formContent['email'])->first();



        if ($user) {
            $system->user()->attach($user, ['is_admin' => false]);
            return redirect('/moje-systemy/' . $system->id)->with('success', 'Uživatel byl přidán');;
        } else {
            return back()->with('error', 'Uživatel nebyl nalezen');
        }
    }
}
