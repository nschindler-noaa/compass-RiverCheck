#ifndef BASIN_H
#define BASIN_H

#include <QStringList>

/** \struct basin
 * \brief A structure to represent a storage basin associated with a dam.
 */
class Basin
{
public:
    Basin ();
    ~Basin ();

    float getMinVolume() const;
    void setMinVolume(float value);

    float getMaxVolume() const;
    void setMaxVolume(float value);

    float getVolume(int index) const;
    void setVolume(int index, const float &value);

private:
    float minVolume;         /**< Minimum allowable volume */
    float maxVolume;         /**< Maximum allowable volume */
    QList<float> volume;      /**< Volume per day (DAYS_IN_SEASON) */
};
//Basin * new_basin ();
//void delete_basin (Basin *bsn);


#endif // BASIN_H
