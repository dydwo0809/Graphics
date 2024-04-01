#version 120                  // GLSL 1.20

varying   vec3 v_color;
varying vec3 v_normal;
varying vec3 v_position;

uniform vec3 u_light_position;
uniform vec3 u_light_ambient;
uniform vec3 u_light_diffuse;
uniform vec3 u_light_specular;

uniform vec3  u_obj_ambient;
uniform vec3  u_obj_diffuse;
uniform vec3  u_obj_specular;
uniform float u_obj_shininess;

uniform vec3 u_camera_position;
uniform mat4 u_view_matrix;


vec3 directional_light() {
	vec3 color = vec3(0.0f);
	vec3 normal = normalize(v_normal);

	vec3 light_dir = normalize(u_light_position);
	
	color += (u_light_ambient * u_obj_ambient);

	float ndotl = max(dot(normal, light_dir), 0.0f);
	color += (ndotl * u_light_diffuse * u_obj_diffuse);

	vec3 view_dir = normalize(u_camera_position - v_position);
	vec3 reflect_dir = reflect(-light_dir, normal);

	float rdotv = max(dot(view_dir, reflect_dir), 0.0f);
	color += (pow(rdotv, u_obj_shininess) * u_light_specular * u_obj_specular);

	return color;
}

void main()
{
	vec3 result = directional_light();
	gl_FragColor = vec4(result, 1.0f);
}
