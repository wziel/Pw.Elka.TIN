#pragma once
/// Zmienna wyliczeniowa określająca stan komponentu ClientSession
/// Unauthorized - klient jeszcze nie zautoryzowany
/// Authorized - klient zautoryzowany
/// Busy - zbyt wielu klientów korzysta z aplikacji
enum SessionState { Unauthorized, Authorized, Busy };