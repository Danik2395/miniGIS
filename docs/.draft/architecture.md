# architecture

## main
Initialize entt::registry,\
set Qt styles,\
create Qt window.

## class QGFrontend

## module gengine

### part gengine:camera
- perform_pan
- perform_zoom
- perform_rotate
- world_to_screen
- screen_to_world
- get_cursor_world_pos

### part gengine:toolbox
- calc_distance_on_selected_objects
- calc_area_on_selected_objects
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
- query_objects_selected
- is_object_selected

### part gengine:validation
- check_self_intersection_?
- check_orientation_?
- check_closed_line

### part gengine:spatial
- rebuild_index
- query_objects_in_aabb
- query_objects_in_point
- query_objects_nearest_to_point

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

## module wrap.Boost
Wraps boost header to use module opportunities.\
Exports only used parts.

## module wrap.EnTT
Wraps entt header to use module opportunities.\
Exports only used parts.
