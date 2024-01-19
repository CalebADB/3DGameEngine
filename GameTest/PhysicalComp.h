#pragma once
#ifndef _GPHYSICALCOMP_H
#define _GPHYSICALCOMP_H

namespace ge
{
	//class PPhysicalRelationship
	//{
	//	math::MVector3 RelPosition = math::MVector3::ZeroVector();
	//	math::MVector3 RelVelocity = math::MVector3::ZeroVector();
	//	math::MVector3 RelForce = math::MVector3::ZeroVector();

	//};
	//class PPhysicalConstraintRelationship
	//{
	//	math::MVector3 RelPosition = math::MVector3::ZeroVector();
	//	math::MVector3 RelVelocity = math::MVector3::ZeroVector();

	//};
	//class PTheoreticalRelationship // 
	//{
	//	math::MVector3 RelPosition = math::MVector3::ZeroVector();
	//	math::MVector3 RelVelocity = math::MVector3::ZeroVector();

	//};

	class GPhysicalComp : public GComp
	{
	private:
		GLfloat Mass = 1.0f;
		
	public:
		GPhysicalComp(const std::string& Name) 
			: 
			GComp(Name) 
		{}

	protected:
		virtual void Update(float deltaTime);


	};
};

#endif //_GCOMP_H