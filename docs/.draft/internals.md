# internals

# assumptions
- No WKT check in math functions, thus they must recieve WKT valid objects
- Epsilon is get from loaded WTK file by the most accurate value
- Values from WKT stored as doubles,\
    but compared as int64_t via quantization with Epsilon accuracy

# The precision problem:

Need to save WKT file diff -> dynamic precision.

geng::Point::operator<=> needed for rtree -> cannot make the precision as a parameter -> compare module.
- If there were only math predicates precision could be set as a parameter of math functions and forwarded to predicates

Compare needs to know file precision and not depend on high level modules -> cache thread_local the variable and set it from above
- Source of truth not held by compare module. It only compares with some precision
- Precision is available without heavy call to registry

How to set variable? -> raii for variable (geng::compare::CacheQuantizePrecision) -> raii for cache encapsulation (geng::Doc)
- Thread that works with particular document will perform comparison with it's precision and won't be infected by it

## How it works:
Serialization system create registry for document,\
frontend init document with it in the `AppState`,\
when some function needs to be called `AppState::current_doc()` (or `AppState::get_doc(AppState::id_current_doc())` for threads) creates `Doc` that creates `CacheQuantizePrecision` with `Doc::reg().ctx().get<Precision>()`.

Document then used to pass into function.

Cached precision will live till the task end and set back to default afterwards.

## Rejected implementations:
- Global access to registry because it invalidates multithreading and creates implicit dependencies
- Middleware dispatcher
- Cache system
- Parameter for math functions

# Existing modules

## gengine.camera
- world_to_screen
- screen_to_world
- get_cursor_world_pos

## gengine.input
- update_viewport
- update_mouse_pos
- update_mouse_buttons
- rotate
- zoom
- pan

## gengine.looprunner
- run_frame_loop

## gengine.render
- query_draw_sequence

## gengine.serialization
Know what files are supported (.gpkg).render
Calls convert system.

- load_data_from_file
- load_data_to_file
- validate_file_wkt

## gengine.math

## gengine.types
All internal pure data engine types.

### gengine.types.primitives

### gengine.types.precision

### gengine.types.render

### gengine.types.camera

### gengine.types.input

## gengine.doc
More than just files.\
Documents have settings and state as well as they are smart wrappers

# Planned modules

## gengine.toolbox
- ruler_on_selected_objects
- area_on_selected_objects
- find_target_to_snap
- toggle_tool

## gengine.selection
- hit_test
- select_object_in_point
- select_object_in_aabb
- deselect_object_in_point
- deselect_all
- query_objects_selected
- is_object_selected

## gengine.validation
Checks whether geometry is WKT valid.
- self_intersection_?
- orientation_?
- closed_?

## gengine.spatial
- rebuild_index
- query_objects_in_aabb
- query_objects_in_point
- query_objects_nearest_to_point
- get_object

## gengine.data_crud
Operation on seen on map entities.

## gengine.convert
- wkb_to_wkt
- wkt_to_wkb

