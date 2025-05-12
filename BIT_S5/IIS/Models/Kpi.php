<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Kpi extends Model
{
    use HasFactory;

    public function device()
    {
        return $this->belongsTo(Device::class);
    }

    public function parameter()
    {
        return $this->belongsTo(Parameter::class);
    }
}
