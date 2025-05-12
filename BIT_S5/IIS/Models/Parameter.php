<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Parameter extends Model
{
    use HasFactory;

    public function device()
    {
        return $this->belongsToMany(Device::class);
    }

    public function type()
    {
        return $this->belongsToMany(Type::class);
    }

    public function kpi()
    {
        return $this->hasMany(Kpi::class);
    }
}
