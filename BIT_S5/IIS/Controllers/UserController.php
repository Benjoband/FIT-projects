<?php

namespace App\Http\Controllers;

use App\Models\User;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;

class UserController extends Controller
{
    public function registration()
    {
        return view('user.registrace');
    }

    public function store(Request $request)
    {
        $formContent = $request->validate([
            'name' => 'required',
            'email' => 'required|email|unique:users,email',
            'password' => 'required|confirmed|min:8',
        ]);

        $formContent['role_id'] = 3; //3 for user

        $formContent['password'] = bcrypt($formContent['password']);

        $user = User::create($formContent);

        auth()->login($user);

        return redirect()->route('my-systems')->with('success', 'Uživatel byl registrován');;
    }


    public function login()
    {
        return view('user.prihlaseni');
    }

    public function authLogin(Request $request)
    {
        
        $formContent = $request->validate([
            'email' => 'required|email',
            'password' => 'required',
        ]);
        
        if (auth()->attempt($formContent)) {
            $request->session()->regenerate();

            if(auth()->user()->role_id == 2){
                return redirect()->route('find-device')->with('success', 'Uspěšně přihlášen');
            }

            return redirect()->route('my-systems')->with('success', 'Uspěšně přihlášen');
        }
        else
        {
            return back()->withErrors([
                'email' => 'The provided credentials do not match.',
            ]);
        }
        
    }

    public function logout(Request $request)
    {
        auth()->logout();

        $request->session()->invalidate();
        $request->session()->regenerateToken();

        return redirect()->route('my-systems')->with('success', 'Uživatel byl odhlášen');
    }

    public function userAll()
    {
        $users = User::all();

        return view('user.vypis_uzivatelu', [
            'users' => $users,
        ]);
    }
}
