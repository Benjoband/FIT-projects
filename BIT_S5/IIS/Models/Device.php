<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Device extends Model
{
    use HasFactory;

    public function system()
    {
        return $this->belongsTo(System::class);
    }

    public function type()
    {
        return $this->belongsTo(Type::class);
    }

    public function parameter()
    {
        return $this->belongsToMany(Parameter::class)->withPivot('value');
    }

    public function kpi()
    {
        return $this->hasMany(Kpi::class);
    }

    public function scopefilter($query, array $filters)
    {
        if(isset($filters['search']))
        {
            $query
                ->where('name', 'like', '%' .request('search').'%')
                ->orWhere('description', 'like', '%'.request('search').'%')
                ->orWhere('location', 'like', '%'.request('search').'%');
        }
    }
}
