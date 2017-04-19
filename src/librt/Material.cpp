#include "Material.h"
#include "Lambertian.h"
#include <stdio.h>

Material::Material(void) : m_shader(new Lambertian(0.9))
{

}

Material::Material(Shader* m_shader_in) : m_shader(m_shader_in)
{

}

Material::~Material(void)
{

}

RGBR_f Material::Shade(Intersection *pIntersection, STVector3 *lightDirection, Light *light)
{
	return m_shader->Shade(pIntersection, lightDirection, light);
}