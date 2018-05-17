#include <igraph.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(void)
{
    igraph_i_set_attribute_table(&igraph_cattribute_table);

    igraph_t graph;
    igraph_vector_t v;
    igraph_vector_t result;
    igraph_real_t edges[] = {
        0, 1,
        0, 2,
        0, 3,
        0, 4,
        1, 5,
        5, 6,
        5, 7,
        7, 8};
    
    bool t[] = {true, false, false, false, false, true, false, false, true};   
    igraph_vector_bool_t types;

    std::vector<std::string> strattrs = {"red", "blue","blue","blue","blue","red","blue","blue","red"};
    igraph_strvector_t colors;
    //igraph_attribute_table_t* attrs;

    igraph_vector_view(&v, edges, sizeof(edges) / sizeof(double));
    //igraph_vector_view(&types, t, sizeof(t) / sizeof(bool));
    
    igraph_vector_bool_init(&types, sizeof(t));
    for(int i = 0; i<igraph_vector_bool_size(&types); ++i){
        VECTOR(types)[i] = t[i];
    }
    igraph_strvector_init(&colors, sizeof(t));
    int i = 0;
    for(auto it: strattrs){
        igraph_strvector_set(&colors, i, it.c_str());
        ++i;
    }

    
    igraph_create_bipartite(&graph, &types, &v, IGRAPH_UNDIRECTED);

    igraph_cattribute_VAS_setv(&graph, "color", &colors);

    igraph_vector_init(&result, 0);

    igraph_degree(&graph, &result, igraph_vss_all(), IGRAPH_ALL,
                  IGRAPH_LOOPS);
    printf("Maximum degree is      %10i, vertex %2i.\n",
           (int)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

    igraph_closeness(&graph, &result, igraph_vss_all(), IGRAPH_ALL,
                     /*weights=*/0, true);
    printf("Maximum closeness is   %10f, vertex %2i.\n",
           (double)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

    igraph_betweenness(&graph, &result, igraph_vss_all(),
                       IGRAPH_UNDIRECTED, /*weights=*/0, /*nobigint=*/1);
    printf("Maximum betweenness is %10f, vertex %2i.\n",
           (double)igraph_vector_max(&result), (int)igraph_vector_which_max(&result));

    std::cout << "Vertex list" << std::endl;
    for (int i=0; i<sizeof(t) ; ++i){
        std::cout << "-" << i << ":" << VAS(&graph, "color", i) << std::endl;
    }


    igraph_matrix_t res;
    igraph_matrix_init(&res, 0, 0);// (int)sizeof(t));
    igraph_layout_bipartite(&graph, &types, &res, 3, 10, 100);

    std::ofstream outfile;
    outfile.open("output.txt");

    for(int i = 0; i < igraph_matrix_nrow(&res);++i){
        for(int j=0; j < igraph_matrix_ncol(&res); ++j){
            outfile << MATRIX(res, i, j) << " ";
        }
        outfile << std::endl;
    }

    igraph_vector_destroy(&result);
    igraph_vector_bool_destroy(&types);
    igraph_destroy(&graph);

    return 0;
}