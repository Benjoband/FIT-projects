<?php

use App\Models\Kpi;
use App\Models\Type;
use App\Models\User;
use App\Models\Device;
use App\Models\System;
use App\Models\Parameter;
use Illuminate\Support\Facades\Route;
use App\Http\Controllers\KpiController;
use App\Http\Controllers\TypeController;
use App\Http\Controllers\UserController;
use App\Http\Controllers\DeviceController;
use App\Http\Controllers\SystemController;
use App\Http\Controllers\ProfileController;
use App\Http\Controllers\ParameterController;
use PHPUnit\Logging\TestDox\TestCreatedMockObjectForAbstractClassSubscriber;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider and all of them will
| be assigned to the "web" middleware group. Make something great!
|
*/

//systeémy
Route::get('/', [SystemController::class, 'systemAll'])->name('my-systems')->middleware('auth');

Route::get('/vytvorit-system', [SystemController::class, 'create'])->name('create-system')->middleware('auth');

Route::post('/vytvorit-system/vytvareni', [SystemController::class, 'store'])->name('store-system')->middleware('auth');

Route::get('/moje-systemy/{system}', [SystemController::class, 'systemOne'])->name('system')->middleware('auth');

Route::get('/moje-systemy/{system}/editace-systemu', [SystemController::class, 'edit'])->name('edit-system')->middleware('auth');

Route::put('/moje-systemy/{system}/editace-systemu/uprava', [SystemController::class, 'update'])->name('update-system')->middleware('auth');

Route::delete('/moje-systemy/{system}/smazat-system', [SystemController::class, 'delete'])->name('delete-system')->middleware('auth');

Route::get('/moje-systemy/{system}/pridat-uzivatele', [SystemController::class, 'addUser'])->name('add-user')->middleware('auth');

Route::post('/moje-systemy/{system}/pridat-uzivatele/pridani', [SystemController::class, 'storeUser'])->name('store-user')->middleware('auth');

Route::get('/prochazet-systemy', [SystemController::class, 'systemFind'])->name('find-system');


//uzivatel
Route::get('/uzivatel/registrace', [UserController::class, 'registration'])->name('registration');

Route::post('/uzivatel', [UserController::class, 'store'])->name('store-user');

Route::post('/uzivatel/autentifikace', [UserController::class, 'authLogin'])->name('authLogin');

Route::get('/uzivatel/prihlaseni', [UserController::class, 'login'])->name('login');

Route::post('/uzivatel/odhlaseni', [UserController::class, 'logout'])->name('logout');

Route::get('/vypis-uzivatelu', [UserController::class, 'userAll'])->name('all-user')->middleware('auth');

//zarizeni
Route::get('/vytvorit-zarizeni', [DeviceController::class, 'create'])->name('create-device')->middleware('auth');

Route::get('/vytvorit-zarizeni/{system}', [DeviceController::class, 'createInSystem'])->name('create-device-in-system')->middleware('auth');

Route::post('/vytvorit-zarizeni/vytvareni', [DeviceController::class, 'store'])->name('store-device')->middleware('auth');

Route::delete('/smazat-zarizeni/{device}', [DeviceController::class, 'delete'])->name('delete-device')->middleware('auth');

Route::get('/editace-zarizeni/{device}', [DeviceController::class, 'edit'])->name('edit-device')->middleware('auth');

Route::get('/prochazet-zarizeni', [DeviceController::class, 'deviceFind'])->name('find-device');

Route::put('/editace-zarizeni/{device}/uprava', [DeviceController::class, 'update'])->name('update-device')->middleware('auth');

//kpi
Route::get('/vytvorit-kpi', [KpiController::class, 'create'])->name('create-kpi')->middleware('auth');

Route::post('/vytvorit-kpi/vytvareni', [KpiController::class, 'store'])->name('store-kpi')->middleware('auth');

Route::delete('/smazat-kpi/mazu', [KpiController::class, 'delete'])->name('delete-kpi')->middleware('auth');

Route::get('/editace-kpi/{kpi}', [KpiController::class, 'edit'])->name('edit-kpi')->middleware('auth');

Route::put('/editace-kpi/{kpi}/uprava', [KpiController::class, 'update'])->name('update-kpi')->middleware('auth');

//typ
Route::get('/vytvorit-typ', [TypeController::class, 'create'])->name('create-type')->middleware('auth');

Route::post('/vytvorit-typ/vytvareni', [TypeController::class, 'store'])->name('store-type')->middleware('auth');


//parameter
Route::get('/vytvorit-parametr', [ParameterController::class, 'create'])->name('create-parameter')->middleware('auth');

Route::post('/vytvorit-parametr/vytvareni', [ParameterController::class, 'store'])->name('store-parameter')->middleware('auth');


Route::get('/editace-hodnot/{device}/{parameter}', [DeviceController::class, 'editValues'])->name('edit-values')->middleware('auth');

Route::put('/editace-hodnot/{device}/{parameter}/uprava', [DeviceController::class, 'updateValues'])->name('update-values')->middleware('auth');


