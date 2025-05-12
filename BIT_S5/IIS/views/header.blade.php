<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link href='https://fonts.googleapis.com/css?family=Nunito' rel='stylesheet'>
  <link href="{{ asset('css/header.css') }}" rel="stylesheet">
  <link href="{{ asset('css/footer.css') }}" rel="stylesheet">
  <link href="{{ asset('css/create.css') }}" rel="stylesheet">
  <link href="{{ asset('css/my_systems.css') }}" rel="stylesheet">
  <link href="{{ asset('css/search_systems.css') }}" rel="stylesheet">
  <link href="{{ asset('css/system.css') }}" rel="stylesheet">
  <link href="{{ asset('css/user.css') }}" rel="stylesheet">
  <link href="{{ asset('css/devices.css') }}" rel="stylesheet">
  <script src="//unpkg.com/alpinejs" defer></script>
</head>
<body>

<div class="header">
<table class="header-table">
    <tr>
        <td class="logo-column"><a href="/"><img class="header-picture" src={{asset('img/logo.png')}}></a></td>
      <td class="buttons-column">
        @auth
        @if(auth()->user()->role_id == 2)
        <div class="header-buttons">
            <a href="{{route('find-device')}}" class="header-button">Přidat data do zařízení</a>
          </div>
        @else
        <div class="header-buttons">
            <a href="{{ route('my-systems') }}" class="header-button">Moje systémy</a>
            <div class="header-button" id="createButton">Vytvořit</div>
            <div class="header-sub-buttons">
              <a href="{{ route('create-type') }}" class="header-sub-button">Typ</a>
              <a href="{{ route('create-device') }}" class="header-sub-button">Zařízení</a>
              <a href="{{ route('create-system') }}" class="header-sub-button">Systém</a>
              <a href="{{ route('create-kpi') }}" class="header-sub-button">KPI</a>
              <a href="{{ route('create-parameter') }}" class="header-sub-button">Parametr</a>
            
          </div>
            <a href="{{ route('find-system') }}" class="header-button">Procházet systémy</a>
          </div>
        @endif
        @else
        <div class="header-buttons">
          <a href="{{ route('my-systems') }}" class="header-button">Moje systémy</a>
          <div class="header-button" id="createButton">Vytvořit</div>
          <div class="header-sub-buttons">
            <a href="{{ route('create-type') }}" class="header-sub-button">Typ</a>
            <a href="{{ route('create-device') }}" class="header-sub-button">Zařízení</a>
            <a href="{{ route('create-system') }}" class="header-sub-button">Systém</a>
            <a href="{{ route('create-kpi') }}" class="header-sub-button">KPI</a>
            <a href="{{ route('create-parameter') }}" class="header-sub-button">Parametr</a>
          
        </div>
          <a href="{{ route('find-system') }}" class="header-button">Procházet systémy</a>
        </div>
        @endauth
      </td>
      <td class="profile-info-column">
        <div class="user-info">
        @auth
        <h2 class="user-name">{{ auth()->user()->name}}</h2>
        <p class="user-email">{{ auth()->user()->email }}</p>
        <form method="POST" action="{{ route('logout') }}">
            @csrf
            <input type="submit" value="Odhlásit se" class="user-logout">
        </form>
        @else
        <form method="get" action="/uzivatel/registrace">
            @csrf
            <input type="submit" value="Registrovat" class="user-buttons">
        </form>
        <form method="get" action="/uzivatel/prihlaseni">
            @csrf
            <input type="submit" value="Přihlásit se" class="user-buttons">
        </form>
        @endauth
        </div>
    </td>
    </tr>
</table>
</div>
<script>
    var createButton = document.getElementById('createButton');
    var subButtons = document.querySelector('.header-sub-buttons');

    createButton.addEventListener('mouseenter', function () {
        subButtons.style.display = 'flex';
    });

    // Add event listeners to hide the sub-buttons
    createButton.addEventListener('mouseleave', function () {
        hideSubButtons();
    });

    document.querySelector('.header-buttons').addEventListener('mouseleave', function (event) {
        // Check if the mouse is not over the create button or sub-buttons
        if (!isMouseOverElement(event, createButton) && !isMouseOverElement(event, subButtons)) {
            hideSubButtons();
        }
    });

    subButtons.addEventListener('mouseenter', function () {
        // Keep the sub-buttons visible when the mouse is over them
        subButtons.style.display = 'flex';
    });

    subButtons.addEventListener('mouseleave', function () {
        // Hide the sub-buttons when the mouse leaves them
        hideSubButtons();
    });

    function hideSubButtons() {
        subButtons.style.display = 'none';
    }

    function isMouseOverElement(event, element) {
        var rect = element.getBoundingClientRect();
        return (
            event.clientX >= rect.left &&
            event.clientX <= rect.right &&
            event.clientY >= rect.top &&
            event.clientY <= rect.bottom
        );
    }
</script>
<x-flash-message />
<div class="help">