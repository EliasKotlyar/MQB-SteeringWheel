import {WEB_SOCKET_ROOT} from '../../api/endpoints';
import {FormLoader, SectionContent} from '../../components';
import {updateValue, useWs} from '../../utils';
import {FormControl, FormControlLabel, FormLabel, Radio, RadioGroup, Typography} from '@mui/material';
import {ShiftRegState} from '../types';
import React, {FC} from 'react';

const WEBSOCKET_URL = WEB_SOCKET_ROOT + "ShiftRegState";

const ShiftStatus: FC = () => {
    const {connected, updateData, data} = useWs<ShiftRegState>(WEBSOCKET_URL);

    //const handleChange =

    const handleChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        updateValue(updateData)(event)
    }


    const content = () => {
        if (!connected || !data) {
            return (<FormLoader message="Connecting to WebSocket…"/>);
        }
        return (
            <>
                <div>State: {data.pin}</div>
                <FormControl>
                    <FormLabel id="demo-controlled-radio-buttons-group">Status of Shift Registers</FormLabel>
                    <RadioGroup
                        aria-labelledby="demo-controlled-radio-buttons-group"
                        name="pin"
                        value={data.pin}
                        onChange={handleChange}
                    >
                        {[...Array(9)].map((x, i) => {
                                var shiftRegisterLabel = "None"
                                if (i != 0) {
                                    shiftRegisterLabel = "Q" + (i);
                                }
                                return (<FormControlLabel value={i} control={<Radio/>} label={shiftRegisterLabel}/>)
                            }
                        )}

                    </RadioGroup>
                </FormControl>


            </>
        );
    };

    return (
        <>
            <SectionContent title='Shift Register State' titleGutter>
                <Typography variant="body1" paragraph>
                    {content()}
                </Typography>
            </SectionContent>

        </>
    );
};

export default ShiftStatus;
