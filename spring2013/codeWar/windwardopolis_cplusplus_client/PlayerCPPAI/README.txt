VS uses the Debug\Release folder under the project root directory. That's where
your exe is, and by default, where your log will go. You can change that in the
app.config if you want.

This is c++/cli, not ansi c++. Here's some help for those not experienced with 
c++/cli.

Don't use pointers, use (tracking) handles - the hat ^ symbol. They are garbage
collected pointers. You can't do pointer arithmetic on them - the addresses 
change. Don't use delete.

Use gcnew instead of new.

Use nullptr instead of NULL or 0.

Use ref class instead of class.

Use safe_cast, e.g., safe_cast<Type>(obj).

Use generics instead of templates.

Use the .NET Framework Class Library instead of the STL. On the MSDN website, 
you can select c++ language examples. 

You can't use linq or lambda expressions. (There's ways to use linq - google if
you really want to.)

Since you're using .NET, it's kind of like C# or Java, but with C++ syntax 
instead. But you do still have to watch out for circular references in your 
headers.

One thing to watch out for, particularly when you're concatenating strings and 
chars, or producing values for the XML messages, is to use L'c' or L"str". L
makes it a wchar_t or System::Char. If you mix them, you might end up with
the wrong string because the byte value is padded up to two bytes and the
character is interpreted as Unicode. 

If you change project configuration in Debug mode, you also have to change it
in Release mode if you want the same settings in Release builds (and vice 
versa.)

Your app.config will only update if you actually run the build command - F5 
debug doesn't always run the build command.