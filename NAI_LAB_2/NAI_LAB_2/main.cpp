#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

/**
 * domain - generate domain points. Throws exception when all the points were returned
 */
auto brute_force = [](auto f, auto domain, int iterations) {
    auto current_p = domain();
    auto best_point = current_p;
    try {
        for (int i = 0; i < iterations; i++){
            while (true) {
                if (f(current_p) < f(best_point)) {
                    best_point = current_p;
                }
                current_p = domain();
            }
        }
    }catch (std::exception &e) {}

    return best_point;
};
using domain_t = std::vector<double>;
std::random_device rd;
std::mt19937 mt_generator(rd());
domain_t hill_climbing(const std::function<double(domain_t)> &f, domain_t minimal_d, domain_t maximal_d, int max_iterations) {
    domain_t current_p(minimal_d.size());
    for (int i = 0; i < minimal_d.size(); i++) {
        std::uniform_real_distribution<double> dist(minimal_d[i], maximal_d[i]);
        current_p[i] = dist(mt_generator);
    }
    for (int iteration = 0; iteration < max_iterations; iteration++) {
        domain_t new_p(minimal_d.size());
        for (int i = 0; i < minimal_d.size(); i++) {
            std::uniform_real_distribution<double> dist(-1.0/128.0, 1.0/128.0);
            new_p[i] = current_p[i] + dist(mt_generator);
        }
        if (f(current_p) > f(new_p)) {
            current_p = new_p;
        }
    }
    return current_p;
}
int main() {

    auto sphere_f = [](double x) {return x*x;};
    double current_sphere_x = -10;
    auto sphere_generator = [&current_sphere_x]() {
        current_sphere_x+= 1.0/128.0;
        if (current_sphere_x >= 10) throw std::invalid_argument("finished");
        return current_sphere_x;
    };

    auto ackley_f = [](double x) {
        return -20 * exp (-0.2 * sqrt(0.5 * (x*x))) - exp(0.5 * (cos(2*M_PI*x) + cos(2*M_PI*x))) + M_E + 20;
    };
    double current_ackley_x = -10;
    auto ackley_generator = [&current_ackley_x](){

        current_ackley_x+= 1.0/128.0;
        if (current_ackley_x >= 10) throw std::invalid_argument("finished");
        return current_ackley_x;
    };
    auto matyas_f = [](double x) {
        return 0.26 * (x*x + x*x) - 0.48 * x * x;
    };
    double current_matyas_x = -10;
    auto matyas_generator = [&current_matyas_x](){
        current_matyas_x+= 1.0/128.0;
        if (current_matyas_x >= 10) throw std::invalid_argument("finished");
        return current_matyas_x;
    };
    auto rastrigin_f = [](double x) {
        return 20 + x*x - 10 * cos(2*M_PI*x) + x*x - 10 * cos(2*M_PI*x);
    };
    double current_rastrigin_x = -10;
    auto rastrigin_generator = [&current_rastrigin_x](){
        current_rastrigin_x+= 1.0/128.0;
        if (current_rastrigin_x >= 10) throw std::invalid_argument("finished");
        return current_rastrigin_x;
    };

    std::cout << "1. Sphere \n 2. Ackley \n 3. Matyas \n 4. Rastrigin \n 5. Generator 20 iteracji :3"<< std::endl;
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1: {
            auto sphere_minimal = brute_force(sphere_f, sphere_generator, 1000);
            std::cout << "Brute force: " << sphere_minimal << std::endl;
            auto sphere_f_v = [](domain_t x) {return x[0]*x[0];};
            auto sphere_hill_climbing = hill_climbing(sphere_f_v, {-10}, {10}, 100000);
            std::cout << "Hill climbing: " << sphere_hill_climbing[0] << std::endl;
            break;
        }
        case 2: {
            auto ackley_minimal = brute_force(ackley_f, ackley_generator, 1000);
            std::cout << "Brute force: " << ackley_minimal << std::endl;
            auto ackley_f_v = [](domain_t x) {return -20 * exp (-0.2 * sqrt(0.5 * (x[0]*x[0] + x[1]*x[1]))) - exp(0.5 * (cos(2*M_PI*x[0]) + cos(2*M_PI*x[1]))) + M_E + 20;};
            auto ackley_hill_climbing = hill_climbing(ackley_f_v, {-10, -10}, {10, 10}, 100000);
            std::cout << "Hill climbing: " << ackley_hill_climbing[0] << std::endl;
            break;
        }
        case 3: {
            auto matyas_minimal = brute_force(matyas_f, matyas_generator, 1000);
            std::cout << "Brute force: " << matyas_minimal << std::endl;
            auto matyas_f_v = [](domain_t x) {return 0.26 * (x[0]*x[0] + x[1]*x[1]) - 0.48 * x[0] * x[1];};
            auto matyas_hill_climbing = hill_climbing(matyas_f_v, {-10, -10}, {10, 10}, 100000);
            std::cout << "Hill climbing: " << matyas_hill_climbing[0] << std::endl;
            break;
        }
        case 4: {

                auto rastrigin_minimal = brute_force(rastrigin_f, rastrigin_generator, 1000);
                std::cout << "Brute force: " << rastrigin_minimal << std::endl;
                auto rastrigin_f_v = [](domain_t x) {
                    return 20 + x[0] * x[0] - 10 * cos(2 * M_PI * x[0]) + x[1] * x[1] - 10 * cos(2 * M_PI * x[1]);
                };
                auto rastrigin_hill_climbing = hill_climbing(rastrigin_f_v, {-10, -10}, {10, 10}, 100000);
                std::cout << "Hill climbing: " << rastrigin_hill_climbing[0] << std::endl;

            break;
        }
        case 5: {
            auto best_point = brute_force(sphere_f, sphere_generator, 100000);
            std::cout << "best x1 = " << best_point << std::endl;
            auto sphere_f_v = [](domain_t x) {return x[0]*x[0];};
            for (int i = 0; i < 20; i++) {
                std::cout << "Pomiar numer:" << i << "Wykonuje iteracji: " << (i + 1) * 100000 << std::endl;
                auto begin = std::chrono::high_resolution_clock::now();
                auto best_sphere = hill_climbing(sphere_f_v, {-10}, {10}, 100000* (i + 1));
                auto end = std::chrono::high_resolution_clock::now();
                auto elapse = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                std::cout << "Czas wykonania: " << elapse.count() << "ms" << std::endl;
                std::cout << "best x2:" << best_sphere[0] << std::endl;
            }
            break;
        }
        default:
            std::cout << "Wrong choice" << std::endl;
    }






    return 0;
}



