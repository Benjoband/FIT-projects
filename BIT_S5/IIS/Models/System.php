<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class System extends Model
{
    use HasFactory;

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

    public function user()
    {
        return $this->belongsToMany(User::class);
    }

    public function device()
    {
        return $this->hasMany(Device::class);
    }
}
