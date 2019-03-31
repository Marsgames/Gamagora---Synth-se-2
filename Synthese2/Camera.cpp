//
//  Camera.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 31/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Camera.hpp"
#include <Vector3.hpp>
#include <Color.hpp>
#include <Pixel.hpp>
#include <math.h>

void Camera::InitImage()
{
    Vector3 baseDirection{0,0,1};
    const double thetaUnsigned = acos((Vector3::Dot(baseDirection, m_direction)));
    const double thetaSigned = m_direction.GetX() >= 0 ? m_direction.GetZ() >= 0 ? thetaUnsigned : thetaUnsigned * -1 : m_direction.GetZ() >= 0 ? thetaUnsigned * -1 : thetaUnsigned;
    m_image.reserve(m_height * m_width);
    Color defaultColor {0, 0, 0};
    
    for (int index = 0; index < m_height * m_width; index++)
    {
        // Pour un écran de 1000 * 1000
        // 0 * 0  -->  1000 * 1000
        //const int x = index % m_width;
        //const int y = index / m_width;
        
        // -500, -500  -->  500, 500
        const int indexX = (index % m_width - m_width / 2);// + m_origin.GetX();
        const int indexY = (index / m_width - m_height / 2);// + m_origin.GetY();
        
        const Vector3 actualPos {indexX, indexY, static_cast<int>(m_origin.GetZ())};
        const Vector3 newPos = Vector3{cos(thetaSigned) * actualPos.GetX() + sin(thetaSigned) * actualPos.GetZ(), actualPos.GetY(), -sin(thetaSigned) * actualPos.GetX() + cos(thetaSigned) * actualPos.GetZ()};
        m_image.push_back(Pixel(newPos, defaultColor));
    }
}

Vector3 Camera::GetFocalDirection(const Vector3& toThatPoint) const
{
    const Vector3 startPoint = m_origin + Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_origin.GetZ());
    const Vector3 focalStart = m_origin + Vector3::Negate(m_direction * m_focal);
    
    return (startPoint - focalStart).Normalize();
}
