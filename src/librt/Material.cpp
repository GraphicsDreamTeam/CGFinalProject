#include "Material.h"

Material::Material(Shader m_shader_in) : m_shader(m_shader_in)
{

}

RGBR_f Material::Shade(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
	return m_shader.Shade(pIntersection, lightDirection, light)
}