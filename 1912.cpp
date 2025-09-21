#include <bits/stdc++.h>
using namespace std;

class MovieRentingSystem {
private:
    map<int, set<pair<int,int>>> available_movies;   // movie -> available (price, shop)
    map<pair<int,int>, int> movie_price;             // (movie, shop) -> price
    set<tuple<int,int,int>> rented_set;              // rented movies: (price, shop, movie)

public:
    MovieRentingSystem(int n, vector<vector<int>>& inventory) {
        // Load initial inventory into data structures
        for (auto &entry : inventory) {
            int shop = entry[0], movie = entry[1], price = entry[2];
            available_movies[movie].insert({price, shop});  // add to available
            movie_price[{movie, shop}] = price;            // store price
        }
    }

    vector<int> search(int movie) {
        // Return up to 5 cheapest shops that have the movie available
        vector<int> top_shops;
        if (available_movies.find(movie) == available_movies.end()) return top_shops;

        for (auto &[price, shop] : available_movies[movie]) {
            top_shops.push_back(shop);
            if (top_shops.size() == 5) break;   // only top 5 shops
        }
        return top_shops;
    }

    void rent(int shop, int movie) {
        // Move movie from available -> rented
        int price = movie_price[{movie, shop}];
        rented_set.insert({price, shop, movie});         // add to rented
        available_movies[movie].erase({price, shop});    // remove from available
    }

    void drop(int shop, int movie) {
        // Move movie from rented -> available
        int price = movie_price[{movie, shop}];
        rented_set.erase({price, shop, movie});          // remove from rented
        available_movies[movie].insert({price, shop});   // add back to available
    }

    vector<vector<int>> report() {
        // Return up to 5 cheapest rented movies
        vector<vector<int>> top_rented;
        for (auto &[price, shop, movie] : rented_set) {
            top_rented.push_back({shop, movie});
            if (top_rented.size() == 5) break;           // only top 5
        }
        return top_rented;
    }
};