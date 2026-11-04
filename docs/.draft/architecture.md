# architecture

## assumptions
1. No WKT check in math functions, thus they must recieve WKT valid objects
2. Epsilon is get from loaded WTK file by the most accurate value
3. Values from WKT stored as doubles,\
    but compared as int64_t via quantization with Epsilon accuracy

## main
Initialize entt::registry,\
set Qt styles,\
create Qt window.

## class QGFrontend

## module gengine

### part gengine:camera
- pan
- zoom
- rotate
- world_to_screen
- screen_to_world
- get_cursor_world_pos

### part gengine:toolbox
- ruler_on_selected_objects
- area_on_selected_objects
- find_target_to_snap
- toggle_tool

### part gengine:input
- update_mouse_position
- update_mouse_state

### part gengine:selection
- hit_test
- select_object_in_point
- select_object_in_aabb
- deselect_object_in_point
- deselect_all
- query_objects_selected
- is_object_selected

### part gengine:validation
Checks whether geometry is WKT valid.
- self_intersection_?
- orientation_?
- closed_?

### part gengine:spatial
- rebuild_index
- query_objects_in_aabb
- query_objects_in_point
- query_objects_nearest_to_point
- get_object

### part gengine:data_crud
Operation on seen on map entities.

### part gengine:render
- run_frame_loop
- query_draw_sequence

### part gengine:serialization
- load_data_from_wkt_file
- load_data_to_wkt_file
- validate_file_wkt

### part gengine:math

## module gengine.types
All internal engine types.

## module gengine.components
ECS components; wraps on internal types.
