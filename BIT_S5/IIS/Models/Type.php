<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Type extends Model
{
    use HasFactory;

    public function device()
    {
        return $this->hasMany(Device::class);
    }

    public function parameter()
    {
        return $this->belongsToMany(Parameter::class);
    }
}
