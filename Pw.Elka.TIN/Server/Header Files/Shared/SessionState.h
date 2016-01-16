#pragma once
/// Zmienna wyliczeniowa okre�laj�ca stan komponentu ClientSession
/// Unauthorized - klient jeszcze nie zautoryzowany
/// Authorized - klient zautoryzowany
/// Busy - zbyt wielu klient�w korzysta z aplikacji
enum SessionState { Unauthorized, Authorized, Busy };