#pragma once
namespace SKC {
    double fac(int x) {
        if (x == 1) return 1;
        if (x == 2) return 2;

        double ret = 2;
        for (int v = 3; v <= x; ++v) {
            ret *= v;
        }
        return ret;
    }
    double choose(int n, int k) {
        double nfac = fac(n);
        double kfac = fac(k);
        double knfac = fac(n - k);
        return nfac / (kfac * knfac);
    }
    long double hypergeometricPDF(
        int population, int totalSuccessStates,
        int draws, int observedSucces
    ) {

        int failsInPop = population - totalSuccessStates;
        int drawFailes = draws - observedSucces;
        double top = (double)choose(totalSuccessStates, observedSucces);
        top *= choose(failsInPop, drawFailes);
        return top / choose(population, draws);
    }
    struct chance_t {
        double less, exact, more;
    };
    chance_t hypergeometricChance(
        int population, int totalSuccessStates,
        int draws, int observedSucces
    ) {
        chance_t ret = { 0,0,0 };
        for (int os = 0; os < observedSucces; ++os) {
            ret.less += hypergeometricPDF(population, totalSuccessStates, draws, os);
        }
        ret.exact = hypergeometricPDF(population, totalSuccessStates, draws, observedSucces);
        ret.more = 1 - (ret.exact + ret.less);
        return ret;
    }
}