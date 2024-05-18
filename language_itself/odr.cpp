
// ORD stands for one-definition rule,
// which is a rule that states that an object or function can only have one definition in the entire program.

// The following entities are exempt from the one-definition rule:
// - types (programs-defined types, like classes, structs, enums, and typedefs)
// - inline functions
// - inline variables
// - templates (function templates, class templates, variable templates, etc.)
// - the instances of a template (because they are potentially inlined)