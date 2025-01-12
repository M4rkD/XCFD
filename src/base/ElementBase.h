#ifndef incl_LagrangeElement_h
#define incl_LagrangeElement_h

#include "headersEigen.h"
//#include "SolutionData.h"
#include <vector>

using std::vector;
using std::cout;


enum MeshConfiguration
{
  CONFIG_ORIGINAL=0, CONFIG_DEFORMED=1
};


enum ElementShapes
{
  ELEM_SHAPE_TRIA=1, ELEM_SHAPE_QUAD=2, 
  ELEM_SHAPE_TETRA=4, ELEM_SHAPE_PYRAMID=5, ELEM_SHAPE_PENTA=6, ELEM_SHAPE_HEXA=8,
  ELEM_SHAPE_TRIA_BERNSTEIN=100, ELEM_SHAPE_TETRA_BERNSTEIN=400,
  ELEM_SHAPE_QUAD_BERNSTEIN=101, ELEM_SHAPE_HEXA_BERNSTEIN=401
};



class ElementBase
{
  public:

    //member variables
    int  ELEM_TYPE;
    int  ndim, degree, npElem, nlbf, ndof, nsize, nGP;
    int  elmType, matType, secType, subdomId;
    double  elemVol, charlen, dtCrit;

    //SolutionData  *SolnData;

    vector<int>  nodeNums, forAssyVec;

    vector<double>  elemVolGP;

    vector<VectorXd>  Nv, dNvdx, dNvdy, dNvdz, Np, dNpdx, dNpdy, dNpdz;


    //member functions

    ElementBase();

    virtual ~ElementBase();

    int getDimension()
    { return ndim; }

    int getPolynomialDegree()
    { return degree; }

    void  setSubdomainId(int sid)
    {  subdomId = sid; return;  }

    int getSubdomainId()
    {  return  subdomId;  }

    int getNodesPerElement()
    {  return  npElem; }

    int getNdofPerNode()
    { return ndof; }

    int  getNdofPerElement()
    {  return  nsize;  }

    std::vector<int>&  getNodeNumbers()
    {  return  nodeNums; }

    std::vector<int>&  getVectorForAssembly()
    {  return  forAssyVec; }

    double getVolume()
    { return  elemVol;  }

    virtual int calcLoadVector(VectorXd& Flocal)
    { cout << "   'calcLoadVector' is not defined for this element!\n\n"; return 0; }

    virtual double  calcCriticalTimeStep(double* elemData, double* timeData, VectorXd&  veloVec)
    { cout << "   'calcCriticalTimeStep' is not defined for this element!\n\n"; return 0.0; }

    virtual  int calcError(int index)
    { cout << "  'calcError' is not available for this element!\n\n"; return -1; }

    virtual void prepareElemData(vector<vector<double> >& node_coods)
    { cout << "   'prepareElemData' is not defined for this element!\n\n"; return; }

    virtual int MassMatrices(vector<vector<double> >& node_coods, double* elemData, VectorXd&  Mlocal1, VectorXd&  Mlocal2)
    { cout << "   'MassMatrices' is not defined for this element!\n\n"; return -1; }

    virtual double  ResidualIncNavStokesAlgo1(vector<vector<double> >& node_coods, double* elemData, double* timeData, VectorXd& veloVec, VectorXd& veloVecPrev, VectorXd& veloDotVec, VectorXd& veloDotVecPrev, VectorXd& presVec, VectorXd& presVecPrev, VectorXd&  Flocal1, VectorXd&  Flocal2, double timeCur)
    { cout << "   'ResidualIncNavStokesAlgo1' is not defined for this element!\n\n"; return -1; }

    virtual int  ResidualIncNavStokesAlgo2(vector<vector<double> >& node_coods, double* elemData, double* timeData, VectorXd& veloCur, VectorXd& acceCur, VectorXd& presCur, VectorXd&  Flocal2)
    { cout << "   'ResidualIncNavStokesAlgo2' is not defined for this element!\n\n"; return -1; }

    virtual double CalculateError(vector<vector<double> >& node_coords, double* elemData, double* timeData, VectorXd& veloPrev, VectorXd& veloDotPrev, VectorXd& presPrev, double timeCur, int index)
    { cout << "   'CalculateError' is not defined for this element!\n\n"; return 0; }

    virtual int  StiffnessAndResidual(vector<vector<double> >& node_coords, double* elemData, double* timeData, VectorXd& solnCur, MatrixXd& Klocal, VectorXd& Flocal, double timeCur)
    { cout << "   'StiffnessAndResidual' is not defined for this element!\n\n"; return -1; }

    virtual int toComputeInfSupCondition(vector<vector<double> >& node_coords, double* elemData, MatrixXd& Kuu, MatrixXd& Kup, MatrixXd& Kpp)
    { cout << "   'toComputeInfSupCondition' is not defined for this element!\n\n"; return -1; }

    virtual int CalculateForces(int side, vector<vector<double> >& node_coords, double* elemData, double* timeData, VectorXd& veloVec, VectorXd& presVec, VectorXd&  Flocal1)
    { cout << "   'CalculateForces' is not defined for this element!\n\n"; return -1; }

};



#endif //incl_Lagrange_Element_h

