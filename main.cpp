#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

long long global_id = 0;   // для строгого старшинства

//--------------------------------------------------
// БАЗОВЫЙ КЛАСС
//--------------------------------------------------
class Animal {
protected:
    int x, y;
    Direction dir;
    int stability;
    int age;
    long long id;     // определяет старшинство

public:
    Animal(int x, int y, int s, Direction d)
        : x(x), y(y), stability(s), dir(d), age(0), id(global_id++) {}

    virtual ~Animal() {}

    virtual void move(int N, int M) = 0;
    virtual int maxAge() const = 0;

    void rotateIfNeeded() {
        if (stability > 0 && age > 0 && age % stability == 0)
            dir = Direction((dir + 1) % 4);
    }

    void grow() { age++; }

    bool isDead() const { return age >= maxAge(); }

    int getX() const { return x; }
    int getY() const { return y; }
    int getAge() const { return age; }
    Direction getDir() const { return dir; }
    int getStability() const { return stability; }
    long long getId() const { return id; }

protected:
    void stepOne(int N, int M) {
        if (dir == NORTH) x = (x - 1 + N) % N;
        if (dir == SOUTH) x = (x + 1) % N;
        if (dir == EAST)  y = (y + 1) % M;
        if (dir == WEST)  y = (y - 1 + M) % M;
    }
};

//--------------------------------------------------
// ЗАЯЦ
//--------------------------------------------------
class Rabbit : public Animal {
public:
    Rabbit(int x, int y, int s, Direction d)
        : Animal(x, y, s, d) {}

    void move(int N, int M) override {
        stepOne(N, M);
    }

    int maxAge() const override { return 10; }
};

//--------------------------------------------------
// ЛИСА
//--------------------------------------------------
class Fox : public Animal {
    int food;

public:
    Fox(int x, int y, int s, Direction d)
        : Animal(x, y, s, d), food(0) {}

    void move(int N, int M) override {
        stepOne(N, M);
        stepOne(N, M);  // лиса двигается на 2 клетки
    }

    int maxAge() const override { return 15; }

    void addFood(int f) { food += f; }
    int getFood() const { return food; }
    void resetFood() { food = 0; }
};

//--------------------------------------------------
// МОДЕЛЬ
//--------------------------------------------------
class Model {
    int N, M, K;
    vector<Rabbit> rabbits;
    vector<Fox> foxes;

public:
    Model(int N, int M, int K) : N(N), M(M), K(K) {}

    void addRabbit(int x, int y, int d, int s) {
        rabbits.emplace_back(x, y, s, Direction(d));
    }

    void addFox(int x, int y, int d, int s) {
        foxes.emplace_back(x, y, s, Direction(d));
    }

    void step() {

        // 1️⃣ ДВИЖЕНИЕ
        for (auto &r : rabbits) r.move(N, M);
        for (auto &f : foxes) f.move(N, M);

        // 2️⃣ ПИТАНИЕ (старшие лисы едят первыми)
        sort(foxes.begin(), foxes.end(),
             [](const Fox &a, const Fox &b) { return a.getId() < b.getId(); });

        vector<bool> rabbitAlive(rabbits.size(), true);

        for (auto &f : foxes) {
            int eaten = 0;
            for (size_t i = 0; i < rabbits.size(); i++) {
                if (rabbitAlive[i] &&
                    rabbits[i].getX() == f.getX() &&
                    rabbits[i].getY() == f.getY()) {
                    rabbitAlive[i] = false;
                    eaten++;
                }
            }
            f.addFood(eaten);
        }

        vector<Rabbit> newRabbits;
        for (size_t i = 0; i < rabbits.size(); i++)
            if (rabbitAlive[i])
                newRabbits.push_back(rabbits[i]);
        rabbits = newRabbits;

        // 3️⃣ СТАРЕНИЕ
        for (auto &r : rabbits) r.grow();
        for (auto &f : foxes) f.grow();

        // смена направления
        for (auto &r : rabbits) r.rotateIfNeeded();
        for (auto &f : foxes) f.rotateIfNeeded();

        // 4️⃣ РАЗМНОЖЕНИЕ
        vector<Rabbit> bornR;
        for (auto &r : rabbits) {
            if (r.getAge() == 5 || r.getAge() == 10)
                bornR.emplace_back(r.getX(), r.getY(),
                                   r.getStability(), r.getDir());
        }
        rabbits.insert(rabbits.end(), bornR.begin(), bornR.end());

        vector<Fox> bornF;
        for (auto &f : foxes) {
            if (f.getFood() >= 2) {
                bornF.emplace_back(f.getX(), f.getY(),
                                   f.getStability(), f.getDir());
                f.resetFood();
            }
        }
        foxes.insert(foxes.end(), bornF.begin(), bornF.end());

        // 5️⃣ ВЫМИРАНИЕ
        rabbits.erase(remove_if(rabbits.begin(), rabbits.end(),
            [](Rabbit &r) { return r.isDead(); }), rabbits.end());

        foxes.erase(remove_if(foxes.begin(), foxes.end(),
            [](Fox &f) { return f.isDead(); }), foxes.end());
    }

    void run() {
        for (int i = 0; i < K; i++)
            step();
    }

    void print() {
        vector<vector<int>> field(N, vector<int>(M, 0));

        for (auto &r : rabbits)
            field[r.getX()][r.getY()]++;

        for (auto &f : foxes)
            field[f.getX()][f.getY()]--;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (field[i][j] == 0)
                    cout << "*";
                else
                    cout << field[i][j];
            }
            cout << "\n";
        }
    }
};

//--------------------------------------------------
// MAIN
//--------------------------------------------------
int main() {
    int N, M, K;
    cin >> N >> M >> K;

    int R, F;
    cin >> R >> F;

    Model model(N, M, K);

    for (int i = 0; i < R; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        model.addRabbit(x, y, d, s);
    }

    for (int i = 0; i < F; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        model.addFox(x, y, d, s);
    }

    model.run();
    model.print();

    return 0;
}
