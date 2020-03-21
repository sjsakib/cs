long get_dt(long s1, long us1, long s2, long us2) {
    return (s1-s2)*1e6 + (us1 - us2);
}
