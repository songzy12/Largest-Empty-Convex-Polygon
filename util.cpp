#include "util.h"
#include "qDebug" //only for output check, can be removed later,

bool toLeft(Vertex* i, Vertex* j, Vertex* k)
{
	return toLeft(i->point(), j->point(), k->point());
}

bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k)
{
	bool isleft = (get<0>(i)*get<1>(j) -get<1>(i)*get<0>(j)
		+get<0>(j)*get<1>(k) -get<1>(j)*get<0>(k)
		+get<0>(k)*get<1>(i) -get<1>(k)*get<0>(i)) > 0;
	return isleft;
}

void visibility(Mesh* starPoly)
{
	starPoly->all_edges()->clear();// clear the vg of the mesh

	for (int index = 0; index < starPoly->polarAngleSortedVector_vertex.size();index++){

		list<Vertex> vertices = starPoly->polarAngleSortedVector_vertex.at(index);
		int N = vertices.size();

		//clear the queue of every point
		list<Vertex>::iterator itor_vertex = vertices.begin();
		while (itor_vertex != vertices.end())
		{
			//Vertex v1 = *itor_vertex;
			itor_vertex->queue2store()->clear();
			itor_vertex++;
		}

		//do process for n-2 points
		itor_vertex = vertices.begin();
		list<Vertex>::iterator itor_vertex_temp = itor_vertex++;
		for (int i = 1; i <= N - 2; i++)
		{
			itor_vertex_temp = itor_vertex++;
			Vertex* v1 = &(*itor_vertex_temp);
			itor_vertex_temp++;
			Vertex* v2 = &(*itor_vertex_temp);
			VG_process(v1, v2, starPoly, index);
		}
	}
	//return starPoly;
}

void VG_process(Vertex* i, Vertex* j, Mesh* starPoly,int index)
{
	if (starPoly->all_edges()->size() == index)
	{
			list<pair<Vertex*, Vertex*>> all_edges_index;
			starPoly->all_edges()->push_back(all_edges_index);
	}
	deque<Vertex*>* Qi = i->queue2store();
	deque<Vertex*>* Qj = j->queue2store();
	while ((!Qi->empty()) && toLeft(Qi->front(), i, j)){
		//PROCEED
		VG_process(Qi->front(), j, starPoly,index);
		//DEQUEUE(Qi)
		Qi->pop_front();
	}
	//ADD(ij)
	starPoly->all_edges()->at(index).push_back({ i, j });
	//ENQUEUE(i,Qj)
	Qj->push_back(i);
	return;
}

/*����vertex list*/
//Mesh* visibility(Mesh* starPoly)
//{
//	starPoly->all_edges()->clear();// clear the vg of the mesh
//	list<Vertex*> vertices = starPoly->vertices();
//	int N = (starPoly->vertices()).size();
//	
//	//clear the queue of every point
//	list<Vertex*>::iterator itor_vertex = vertices.begin();
//	while (itor_vertex != vertices.end())
//	{
//		Vertex* v1 = *itor_vertex;
//		(*itor_vertex)->queue2store()->clear();
//		itor_vertex++;
//	}
//
//	//do process for n-2 points
//	itor_vertex = vertices.begin();
//	list<Vertex*>::iterator itor_vertex_temp = itor_vertex++;
//	for (int i = 1; i<=N - 2; i++)
//	{
//		itor_vertex_temp = itor_vertex++;
//		Vertex* v1 = *itor_vertex_temp;
//		itor_vertex_temp++;
//		Vertex* v2 = *itor_vertex_temp;
//		VG_process(v1, v2,starPoly);
//	}
//	vertices.clear();
//	return starPoly;
//}
//
//void VG_process(Vertex* i, Vertex* j, Mesh* starPoly)
//{
//	deque<Vertex*>* Qi = i->queue2store();
//	deque<Vertex*>* Qj = j->queue2store();
//	while ((!Qi->empty()) && toLeft(Qi->front(),i,j)){
//	//PROCEED
//		VG_process(Qi->front(), j, starPoly);
//	//DEQUEUE(Qi)
//		Qi->pop_front();
//	}
//	//ADD(ij)
//	starPoly->all_edges()->push_back({ i, j });
//
//	//ENQUEUE(i,Qj)
//		Qj->push_back(i);
//	return;
//}