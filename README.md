# SimpleStringBuilder

Small header-only library which enhances usage of QString::arg function and allows to replicate it for other string classes.

The interface is pretty intiutive for those familiar with QString class from Qt library framework and more precisely [QString::arg](http://doc-snapshots.qt.io/4.8/qstring.html#arg) function that could be described as:

String should contain patterns `%1`, `%2` ... , `%n` that could be replaced by type-safe member function `arg` which accepts `string`, `integer`, `double` and `character` as its first argument. For every argument some additional options (depending on type) could be specified. For string there's also multiple arguments version which accepts up to 10 stirngs. All of the calls to `arg` return reference to the original string so they could be chained.

Improvements done in `SimpleStringBuilder`:
* Every option for replacement is specified separately by set function and stored as a state inside a class. It makes impossible to make a mistake in argument order (especially since mostly it's `int` or types `int` converts to) and allows reusing of the same state for several arguments and possibly even for construction of several strings. These functions are also chainable.
* Variadic template version is implemented. Since every argument is separated from its options it's easy to implement variadic template member function which will call appropriate function for each argument consequently.

Another thing which I implemented here is the class with the same behavior for `std::basic_string<CharT>` (i.e. `std::string` or `std::wstring`)

##Interface:

`QStringBuilder` defined in `QStringBuilder.h` - works with `QString`

`StdStringBuilder` and `StdWstringBuilder` defined in `BasicStringBuilder.h` - work with `std::string` and `std::wstring` respectively.
