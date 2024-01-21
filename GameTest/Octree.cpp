#include "stdafx.h"

namespace ge {

    static int MAX_OBJECTS_PER_NODE = 6;
    static GLfloat MIN_NODE_SIZE = 5.0f;

    void GOctreeNode::Initialize(const math::MVector3& Center, float Size)
    {
        this->Center = Center;
        this->Size = Size;
        bIsLeafNode = true;
    }

    bool GOctreeNode::Insert(GPhysicalComp* PhysicalComp) {
        // Check if the object fits within this node
        if (!IsObjectWithinBounds(PhysicalComp)) {
            // Object does not fit within this node
            return false;
        }

        if (bIsLeafNode) {
            // Add the object if this is a leaf node
            PhysicalComps.push_back(PhysicalComp);

            // Subdivide the node if it exceeds the capacity and is not at the minimum size
            if (PhysicalComps.size() > MAX_OBJECTS_PER_NODE && Size > MIN_NODE_SIZE) {
                Subdivide();
                // Redistribute objects among Children
                for (GPhysicalComp* PhysicalComp : PhysicalComps) {
                    for (GOctreeNode* Child : Children) {
                        if (Child->Insert(PhysicalComp)) {
                            break; // Object was added to a Child, no need to check other Children
                        }
                    }
                }
                PhysicalComps.clear(); // Clear the objects as they are now stored in Children
            }
        }
        else {
            // If not a leaf node, try to insert the object into a Child node
            for (GOctreeNode* Child : Children) {
                if (Child->Insert(PhysicalComp)) {
                    return true; // Object was added to a Child
                }
            }
        }
        return true;
    }
    void GOctreeNode::Remove(GPhysicalComp* PhysicalComp) {
        if (bIsLeafNode) {
            // Remove the object from this node
            PhysicalComps.erase(std::remove(PhysicalComps.begin(), PhysicalComps.end(), PhysicalComp), PhysicalComps.end());
        }
        else {
            // If not a leaf node, try to remove the object from a Child node
            for (GOctreeNode* Child : Children) {
                Child->Remove(PhysicalComp);
            }

            // Optional: Consider merging Child nodes if they are underpopulated
            // ...
        }
    }
    std::vector<GPhysicalComp*> GOctreeNode::GetPossibleCollisions(GPhysicalComp* PhysicalComp) {
        std::vector<GPhysicalComp*> PossibleCollisions;

        // Check if the object is in this node
        if (!IsObjectWithinBounds(PhysicalComp)) {
            return PossibleCollisions; // Return an empty vector if the object is not within this node
        }

        // Add all objects in the current node
        PossibleCollisions.insert(PossibleCollisions.end(), PhysicalComps.begin(), PhysicalComps.end());

        // If this is a leaf node, return the objects in this node
        if (bIsLeafNode) {
            return PossibleCollisions;
        }

        // If this is not a leaf node, also check Children nodes
        for (auto& Child : Children) {
            // Check if the object intersects with the Child node
            if (Child->DoesIntersectWithNode(PhysicalComp)) {
                auto ChildCollisions = Child->GetPossibleCollisions(PhysicalComp);
                PossibleCollisions.insert(PossibleCollisions.end(), ChildCollisions.begin(), ChildCollisions.end());
            }
        }

        return PossibleCollisions;
    }


    bool GOctreeNode::IsObjectWithinBounds(GPhysicalComp* PhysicalComp) const {
        // Get the position of the object
        math::MVector3 Position = PhysicalComp->GetGlobalTransformData().Position;

        // Calculate the boundaries of the node
        GLfloat HalfSize = Size / 2.0f;
        math::MVector3 MinBounds = Center - math::MVector3(HalfSize, HalfSize, HalfSize);
        math::MVector3 MaxBounds = Center + math::MVector3(HalfSize, HalfSize, HalfSize);

        // Check if the object's position is within the node's boundaries
        return (Position.X >= MinBounds.X && Position.X <= MaxBounds.X) &&
            (Position.Y >= MinBounds.Y && Position.Y <= MaxBounds.Y) &&
            (Position.Z >= MinBounds.Z && Position.Z <= MaxBounds.Z);
    }

    void GOctreeNode::Subdivide() {
        // The size of each Child node is half the size of the current node
        GLfloat ChildSize = Size / 2.0f;

        // The offset to calculate the center of each Child node
        GLfloat Offset = ChildSize / 2.0f;

        // Clear existing Children (if any)
        Children.clear();
        Children.reserve(8); // Reserve space for 8 Children

        // Create 8 Children with appropriate centers
        for (int X = -1; X <= 1; X += 2) {
            for (int Y = -1; Y <= 1; Y += 2) {
                for (int Z = -1; Z <= 1; Z += 2) {
                    math::MVector3 ChildCenter = Center + math::MVector3(Offset * X, Offset * Y, Offset * Z);
                    GOctreeNode* OctreeNode = GAMEWORLD->NewObject<GOctreeNode>("OctreeNode");
                    OctreeNode->Initialize(ChildCenter, ChildSize);
                    Children.emplace_back(OctreeNode);
                }
            }
        }

        // The current node is no longer a leaf node
        bIsLeafNode = false;
    }


    bool GOctreeNode::DoesIntersectWithNode(GPhysicalComp* PhysicalComp) const {
        // Get the position and size of the object
        math::MVector3 PhysicalCompPosition = PhysicalComp->GetGlobalTransformData().Position;
        GLfloat PhysicalCompSize = PhysicalComp->GetMaxSize(); // This could be a scalar or a vector, depending on your implementation

        // Calculate the boundaries of the node
        GLfloat HalfSize = Size / 2.0f;
        math::MVector3 MinBounds = Center - math::MVector3(HalfSize, HalfSize, HalfSize);
        math::MVector3 MaxBounds = Center + math::MVector3(HalfSize, HalfSize, HalfSize);

        // Check if the object's area intersects with the node's area
        // Adjust the logic if objSize is a vector
        return (PhysicalCompPosition.X - PhysicalCompSize <= MaxBounds.X && PhysicalCompPosition.X + PhysicalCompSize >= MinBounds.X) &&
            (PhysicalCompPosition.Y - PhysicalCompSize <= MaxBounds.Y && PhysicalCompPosition.Y + PhysicalCompSize >= MinBounds.Y) &&
            (PhysicalCompPosition.Z - PhysicalCompSize <= MaxBounds.Z && PhysicalCompPosition.Z + PhysicalCompSize >= MinBounds.Z);
    }

    void GOctree::Initialize(const math::MVector3& WorldCenter, float WorldSize)
    {
        RootNode = GAMEWORLD->NewObject<GOctreeNode>("OctreeRootNode");
        RootNode->Initialize(WorldCenter, WorldSize);
    }

    void GOctree::Insert(GPhysicalComp* PhysicalComp) {
        RootNode->Insert(PhysicalComp);
    }

    void GOctree::Remove(GPhysicalComp* PhysicalComp) {
        RootNode->Remove(PhysicalComp);
    }

    std::vector<GPhysicalComp*> GOctree::GetPossibleCollisions(GPhysicalComp* PhysicalComp) {
        // If the PhysicalComp is null, return an empty vector
        if (!PhysicalComp) {
            return std::vector<GPhysicalComp*>();
        }

        // Start the collision search from the root node
        return RootNode->GetPossibleCollisions(PhysicalComp);
    }
} 

