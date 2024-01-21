#ifndef _GOCTREE_H
#define _GOCTREE_H

namespace ge {

    class GOctreeNode : public GObject
    {
    private:
        math::MVector3 Center = math::MVector3::ZeroVector();
        GLfloat Size;
        std::vector<GOctreeNode*> Children;
        std::vector<GPhysicalComp*> PhysicalComps;
        bool bIsLeafNode = true;

    public:
        // Constructor, getters, setters
        GOctreeNode(const std::string& Name)
            :
            GObject(Name)
        {}
        void Initialize(const math::MVector3& Center, float Size);
        bool Insert(GPhysicalComp* PhysicalComp);
        void Remove(GPhysicalComp* PhysicalComp);
        std::vector<GPhysicalComp*> GetPossibleCollisions(GPhysicalComp* PhysicalComp);

        bool IsObjectWithinBounds(GPhysicalComp* PhysicalComp) const;
        void Subdivide();
        bool DoesIntersectWithNode(GPhysicalComp* PhysicalComp) const;
    };

    class GOctree : public GObject 
    {
    private:
        GOctreeNode* RootNode = nullptr;
    public:
        GOctree(const std::string& Name)
            :
            GObject(Name)
        {};
        void Initialize(const math::MVector3& WorldCenter, float WorldSize);
        void Insert(GPhysicalComp* PhysicalComp);
        void Remove(GPhysicalComp* PhysicalComp);
        std::vector<GPhysicalComp*> GetPossibleCollisions(GPhysicalComp* PhysicalComp);
    };

} 

#endif // _GOCTREE_H
