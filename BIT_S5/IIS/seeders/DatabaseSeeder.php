<?php

namespace Database\Seeders;

// use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use App\Models\Kpi;
use App\Models\Role;
use App\Models\Type;
use App\Models\User;
use App\Models\Device;
use App\Models\System;
use App\Models\Parameter;
use App\Models\SystemUser;
use App\Models\TypeParameter;
use App\Models\DeviceParameter;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\Hash;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     */
    public function run(): void
    {
        $this->create_types();
        $this->create_parameters();
        $this->create_roles();
        $this->create_users();
        $this->create_systems();
        $this->create_devices();
        $this->create_kpis();
        $this->create_SystemUser();
        $this->create_TypeParameter();
        $this->create_DeviceParameter();
        
    }

    private function create_roles(): void
    {
        Role::factory()->create([
            'name' => 'admin'
        ]);

        Role::factory()->create([
            'name' => 'broker'
        ]);

        Role::factory()->create([
            'name' => 'user'
        ]);
    }

    private function create_DeviceParameter(): void
    {
        DeviceParameter::factory()->create([
            'device_id' => 1,
            'parameter_id' => 1,
            'value' => '22,5'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 2,
            'parameter_id' => 6,
            'value' =>  '19:35:05'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 3,
            'parameter_id' => 4,
            'value' =>  '78'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 4,
            'parameter_id' => 1,
            'value' =>  '18'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 4,
            'parameter_id' => 2,
            'value' =>  '51'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 5,
            'parameter_id' => 6,
            'value' =>  '10:48:06'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 6,
            'parameter_id' => 5,
            'value' =>  '7'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 7,
            'parameter_id' => 1,
            'value' =>  '15'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 7,
            'parameter_id' => 3,
            'value' =>  '1100'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 8,
            'parameter_id' => 7,
            'value' =>  '20'
        ]);

        DeviceParameter::factory()->create([
            'device_id' => 8,
            'parameter_id' => 1,
            'value' =>  '60'
        ]);
        
        DeviceParameter::factory()->create([
            'device_id' => 9,
            'parameter_id' => 1,
            'value' =>  '-5'
        ]);


    }

    private function create_TypeParameter(): void
    {
        TypeParameter::factory()->create([
            'type_id' => 1,
            'parameter_id' => 1
        ]);

        TypeParameter::factory()->create([
            'type_id' => 2,
            'parameter_id' => 1
        ]);

        TypeParameter::factory()->create([
            'type_id' => 2,
            'parameter_id' => 3
        ]);

        TypeParameter::factory()->create([
            'type_id' => 3,
            'parameter_id' => 1
        ]);

        TypeParameter::factory()->create([
            'type_id' => 3,
            'parameter_id' => 2
        ]);

        TypeParameter::factory()->create([
            'type_id' => 4,
            'parameter_id' => 1
        ]);

        TypeParameter::factory()->create([
            'type_id' => 4,
            'parameter_id' => 7
        ]);

        TypeParameter::factory()->create([
            'type_id' => 4,
            'parameter_id' => 1
        ]);

        TypeParameter::factory()->create([
            'type_id' => 5,
            'parameter_id' => 5
        ]);

        TypeParameter::factory()->create([
            'type_id' => 6,
            'parameter_id' => 6
        ]);

        TypeParameter::factory()->create([
            'type_id' => 7,
            'parameter_id' => 4
        ]);
    }

    private function create_SystemUser(): void
    {
        SystemUser::factory()->create([
            'user_id' => 1,
            'system_id' => 1,
            'is_admin' => true
        ]);

        SystemUser::factory()->create([
            'user_id' => 1,
            'system_id' => 2,
            'is_admin' => true
        ]);

        SystemUser::factory()->create([
            'user_id' => 1,
            'system_id' => 3,
            'is_admin' => true
        ]);

        SystemUser::factory()->create([
            'user_id' => 2,
            'system_id' => 3
        ]);

        SystemUser::factory()->create([
            'user_id' => 2,
            'system_id' => 4,
            'is_admin' => true
        ]);
    }

    private function create_kpis(): void
    {
        Kpi::factory()->create([
            'name' => 'Teplota v obýváku je větší než 20°C',
            'status' => true,
            'operator' => '>',
            'value' => 20,
            'device_id' => 1,
            'parameter_id' => 1
        ]);

        Kpi::factory()->create([
            'name' => 'Vlkost v ložnici je větší než 65%',
            'status' => false,
            'operator' => '>',
            'value' => 65,
            'device_id' => 4,
            'parameter_id' => 2
        ]);

        Kpi::factory()->create([
            'name' => 'Tlak v garáži je větší než 1000 hPa',
            'status' => true,
            'operator' => '>',
            'value' => 1000,
            'device_id' => 7,
            'parameter_id' => 3
        ]);

        Kpi::factory()->create([
            'name' => 'Teplota v garáži je menší než -5°C',
            'status' => false,
            'operator' => '<',
            'value' => -5,
            'device_id' => 7,
            'parameter_id' => 1
        ]);

        Kpi::factory()->create([
            'name' => 'Hmotnost je větší než 80 kg',
            'status' => false,
            'operator' => '>',
            'value' => 80,
            'device_id' => 3,
            'parameter_id' => 4
        ]);
    }

    private function create_devices(): void
    {
        Device::factory()->create([
            'name' => 'Teploměr v obýváku',
            'description' => '',
            'location' => 'Obývák',
            'system_id' => 1,
            'type_id' => 1
        ]);

        Device::factory()->create([
            'name' => 'Hodiny v obýváku',
            'description' => '',
            'location' => 'Obývák',
            'system_id' => 1,
            'type_id' => 6
        ]);

        Device::factory()->create([
            'name' => 'Váha',
            'description' => '',
            'location' => 'Obývák',
            'system_id' => 1,
            'type_id' => 7
        ]);        

        Device::factory()->create([
            'name' => 'Teploměr v ložnici',
            'description' => '',
            'location' => 'Ložnice',
            'system_id' => 2,
            'type_id' => 3
        ]);

        Device::factory()->create([
            'name' => 'Hodiny v ložnici',
            'description' => '',
            'location' => 'Ložnice',
            'system_id' => 2,
            'type_id' => 6
        ]);

        Device::factory()->create([
            'name' => 'Monitor spánku',
            'description' => '',
            'location' => 'Ložnice',
            'system_id' => 2,
            'type_id' => 5
        ]);

        Device::factory()->create([
            'name' => 'Thermomanometr v garáži',
            'description' => '',
            'location' => 'Garáž',
            'system_id' => 3,
            'type_id' => 2
        ]);

        Device::factory()->create([
            'name' => 'Tepelné čerpadlo',
            'description' => '',
            'location' => 'Garáž',
            'system_id' => 3,
            'type_id' => 4
        ]);

        Device::factory()->create([
            'name' => 'Teploměr v zahradě',
            'description' => '',
            'location' => 'Zahrada',
            'system_id' => 4,
            'type_id' => 1
        ]);

    }

    private function create_parameters(): void
    {
        Parameter::factory()->create([
            'name' => 'Teplota',
            'unit' => '°C'
        ]);

        Parameter::factory()->create([
            'name' => 'Vlhkost',
            'unit' => '%'
        ]);

        Parameter::factory()->create([
            'name' => 'Tlak',
            'unit' => 'hPa'
        ]);

        Parameter::factory()->create([
            'name' => 'Hmotnost',
            'unit' => 'kg'
        ]);

        Parameter::factory()->create([
            'name' => 'Počet hodin',
            'unit' => 'h',
        ]);

        Parameter::factory()->create([
            'name' => 'Čas',
            'unit' => 'h:min:s',
        ]);

        Parameter::factory()->create([
            'name' => 'Průtok',
            'unit' => 'l/min',
        ]);
    }

    private function create_systems(): void
    {
        System::factory()->create([
            'name' => 'Obývák',
            'description' => 'Zařízení v obýváku',
            'location' => 'První patro obývák',
        ]);

        System::factory()->create([
            'name' => 'Ložnice',
            'description' => 'Zařízení v ložnice',
            'location' => '',
        ]);

        System::factory()->create([
            'name' => 'Garáž',
            'description' => 'Zařízení v garáži',
            'location' => 'Garáž doma',
        ]);
        System::factory()->create([
            'name' => 'Zahrada',
            'description' => 'Zařízení na zahradě',
            'location' => 'Zahrada doma',
        ]);
    }

    private function create_types(): void
    {
        Type::factory()->create([
            'name' => 'Teploměr dallas',
            'description' => 'Teploměr schválený panem Ing. Ladislavem Opiolem',
        ]);

        Type::factory()->create([
            'name' => 'Thermomanometr',
            'description' => 'Teploměr s manometrem',
        ]);

        Type::factory()->create([
            'name' => 'Teploměr s vlhkoměrem',
            'description' => 'Teploměr s vlhkoměrem',
        ]);

        Type::factory()->create([
            'name' => 'Tepelné čerpadlo',
            'description' => '',
        ]);

        Type::factory()->create([
            'name' => 'Monitor spánku',
            'description' => '',
        ]);

        Type::factory()->create([
            'name' => 'Hodiny',
            'description' => '',
        ]);

        Type::factory()->create([
            'name' => 'Váha',
            'description' => '',
        ]);
    }

    private function create_users(): void
    {
        User::factory()->create([
            'name' => 'Patrik Olszar',
            'email' => 'xolsza00@stud.fit.vutbr.cz',
            'password' => Hash::make('admin'),
            'role_id' => 1,
        ]); 

        User::factory()->create([
            'name' => 'Alexej Beňuš',
            'email' => 'xbenus01@stud.fit.vutbr.cz',
            'password' => Hash::make('admin'),
            'role_id' => 1,
        ]);

        User::factory()->create([
            'name' => 'Broker',
            'email' => 'broker@broker.cz',
            'password' => Hash::make('broker'),
            'role_id' => 2,
        ]);

        User::factory()->create([
            'name' => 'Pepa Zdepa',
            'email' => 'peza@zdepa.cz',
            'password' => Hash::make('uzivatel'),
            'role_id' => 3,
        ]);
    }
}
