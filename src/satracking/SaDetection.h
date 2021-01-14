/// \file SaDetection.h
/// \brief SaDetection class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2021

#pragma once

#include <string>

#include "satrackingExport.h"

/// \class SDetection
/// \brief Conatainer for a detection information
class SATRACKING_EXPORT SaDetection{

public:
    /// \fn SaDetection();
    /// \brief Constructor
    SaDetection();
    /// \fn SaDetection(float x, float y, float z, int t);
    /// \brief Constructor
    /// \param[in] x X position of the particle
    /// \param[in] y Y position of the particle
    /// \param[in] z Z position of the particle
    /// \param[in] t Time position of the particle
    SaDetection(float x, float y, float z, int t);
    /// \fn SaDetection(float x, float y, float z, int t, float* features, unsigned int featuresCount);
    /// \brief Constructor
    /// \param[in] x X position of the particle
    /// \param[in] y Y position of the particle
    /// \param[in] z Z position of the particle
    /// \param[in] t Time position of the particle
    /// \param[in] features Vector of extra features
    /// \param[in] featuresCount Size of the feature vector
    SaDetection(float x, float y, float z, int t, float* features, unsigned int featuresCount);

public:
    /// \fn void setX(float x);
    /// \brief Setter for the position x
    /// \param[in] x X position of the particle
    void setX(float x);
    /// \fn void setY(float y);
    /// \brief Setter for the position y
    /// \param[in] y Y position of the particle
    void setY(float y);
    /// \fn void setZ(float z);
    /// \brief Setter for the position z
    /// \param[in] z Z position of the particle
    void setZ(float z);
    /// \fn void setT(float t);
    /// \brief Setter for the position t
    /// \param[in] t T position of the particle
    void setT(int t);
    /// \fn void setFeatures(float* features, unsigned int size);
    /// \brief Setter for the extra features
    /// \param[in] features Vector of extra features
    /// \param[in] featuresCount Size of the feature vector
    void setFeatures(float* features, unsigned int size);

public:
    /// \fn float x();
    /// \brief Getter for the x position
    /// \returns the x position of the detection
    float x();
    /// \fn float y();
    /// \brief Getter for the y position
    /// \returns the y position of the detection
    float y();
    /// \fn float z();
    /// \brief Getter for the z position
    /// \returns the z position of the detection
    float z();
    /// \fn float t();
    /// \brief Getter for the t position
    /// \returns the time position of the detection
    int t();
    /// \fn float features();
    /// \brief Getter for the extra features vector
    /// \returns a pointer to the extra features vector
    float* features();
    /// \fn float featuresCount();
    /// \brief Getter for the extra features vector length
    /// \returns length of the extra features vector
    unsigned int featuresCount();
    /// \fn float feature(unsigned int idx);
    /// \brief Getter for one extra feature
    /// \param[in] idx Position of the feature in the vector
    /// \return the value of the feature
    float feature(unsigned int idx);

protected:
    float m_x; ///< X position of the particle
    float m_y; ///< Y position of the particle
    float m_z; ///< Z position of the particle 
    int m_t; ///< Time position of the particle 
    float* m_features; ///< Vector of extra features
    unsigned int m_featuresCount; ///< Size of the feature vector

};
