///////////////////////////////////////////////////////////////////////////
//	 _________  __   ____  ___  __  _______  __________  ___
//	/ ___/ __ \/ /  / __ \/ _ \/  |/  / __ \/_  __/ __ \/ _ \
// / /__/ /_/ / /__/ /_/ / , _/ /|_/ / /_/ / / / / /_/ / , _/
// \___/\____/____/\____/_/|_/_/  /_/\____/ /_/  \____/_/|_|alpha.
//
//  Daniel Berio 2008-2014
//	http://www.enist.org/
//
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "SkeletonAnimSystem.h"
#include "colormotor.h"

namespace cm
{
    
Vec3 Bone::getEndPos() const
{
    return b->worldMatrix.trans();
}
    
Vec3 Bone::getStartPos() const
{
    return a->worldMatrix.trans();
}
    
    
float Bone::getLength() const
{
    return cm::distance(getStartPos(),getEndPos());
}

void Bone::update()
{
    matrix.identity();
    
    Vec3 d = b->getRestPosition()-a->getRestPosition();
    d.normalize();
    
    matrix.identity();
    Quat qd;
    qd.direction(-d);
    matrix = (M44)qd;//.pointAt(Vec3(0,0,0),d);//,a->worldMatrix.y());
    matrix = a->worldMatrix*matrix;
    matrix *= transform;
    
    /*
    gfx::color(1,0,1);
    gfx::drawLine(getStartPos(),getEndPos());
    gfx::drawAxis(matrix,1.0);
    gfx::color(0,0,1);
    gfx::drawLine(matrix.trans(),matrix.trans()+matrix.z()*getLength());*/
}


SkeletonAnimSystem::SkeletonAnimSystem()
    :
skel(0),
skelAnim(0)
{
}

SkeletonAnimSystem::~SkeletonAnimSystem()
{
    SAFE_DELETE(skel);
    for(AnimMap::iterator it = animMap.begin(); it != animMap.end(); it++ )
        delete it->second;
    DELETE_VECTOR(bones);
}

void SkeletonAnimSystem::addAnimSource( const std::string & name, SkeletonAnimSource * src )
{
    animMap[name] = src;
}
    
bool SkeletonAnimSystem::addBVHFile( const std::string & name, const std::string & path )
{
    BVHParser bvh;
    bvh.parse(path.c_str());
//        return false;
    if(!skel)
    {
        skel = bvh.createSkeleton();
        skelAnim = new SkeletonAnimLayer(skel->getNumJoints());
        skel->update();
    }
    else
    {
        Skeleton * s = bvh.createSkeleton();
        if(s->getNumJoints() != skel->getNumJoints())
        {
            assert(0);
            return false;
        }
        delete s;
    }
    
    SkeletonKeyAnimSource * src = bvh.createAnimation();
    
    
    if(animMap.find(name) != animMap.end())
    {
        debugPrint("Anim map %s already there!\n",name.c_str());
    }
    
    animMap[name] = src;
    
    return true;
}

void SkeletonAnimSystem::play( const std::string & name )
{
    if(animMap.find(name)==animMap.end())
    {
        debugPrint("Could not find %s\n",name.c_str());
        return;
    }
    
    debugPrint("Playing %s\n",name.c_str());
    skelAnim->playAnimation(animMap[name]);
}


void SkeletonAnimSystem::update( float msecs )
{
    skelAnim->update(msecs);
    skel->copyPose(skelAnim->pose);
    skel->update();
    for( int i = 0; i < bones.size(); i++ )
    {
        bones[i]->update();
    }
}
    
std::vector<M44> SkeletonAnimSystem::getBoneMatrices() const
{
    std::vector<M44> M;
    for( int i = 0; i < getNumBones(); i++ )
        M.push_back(bones[i]->matrix);
    return M;
}
    
std::vector<float> SkeletonAnimSystem::getBoneLengths() const
{
    std::vector<float> L;
    for( int i = 0; i < getNumBones(); i++ )
        L.push_back(bones[i]->getLength());
    return L;
}
    
Joint * SkeletonAnimSystem::getJoint(int index)
{
    return skel->getJoint(index);
}
    
int SkeletonAnimSystem::getNumJoints() const
{
    return skel->getNumJoints();
}
    
Bone *SkeletonAnimSystem::addBone( const std::string & joint1, const std::string & joint2, const M44 & transform )
{
    int i;
    i = skel->getJointIndex(joint1);
    if(i<0)
    {
        cm::debugPrint("Could not find bone %s\n",joint1.c_str());
        return 0;
    }
    Joint * a = skel->getJoint(i);
    
    i = skel->getJointIndex(joint2);
    if(i<0)
    {
        cm::debugPrint("Could not find bone %s\n",joint2.c_str());
        return 0;
    }
    
    Joint * b = skel->getJoint(i);
    

    Bone * ab = new Bone(a,b,transform);
    bones.push_back( ab );
    return ab;
}



}