import {WEB_SOCKET_ROOT} from '../../api/endpoints';
import {ButtonRow, FormLoader, SectionContent} from '../../components';
import {updateValue, useWs} from '../../utils';
import {Button, FormControl, FormControlLabel, FormLabel, Radio, RadioGroup, Typography} from '@mui/material';
import {ConfigData} from '../types';
import React, {FC, useState} from 'react';
import SaveIcon from "@mui/icons-material/Save";
import {ValidateFieldsError} from "async-validator";

const CONFIG_SETTING_URL = WEB_SOCKET_ROOT + "ConfigState";

const Config: FC = () => {
    const {connected, updateData, data ,setData , setTransmit} = useWs<ConfigData>(CONFIG_SETTING_URL);

    //
    const handleChange = (event: React.ChangeEvent<HTMLTextAreaElement>) => {
        let configData : ConfigData ={
            mapping : JSON.parse(event.target.value)
        };
        setData(configData)
    }
    const saveChange = (event: React.MouseEvent<HTMLButtonElement>) => {
        setTransmit(true);
    }
    const textData = JSON.stringify(data, null, 2);

    const [text, setFieldErrors] = useState(textData);
    
    const content = () => {

        if (!connected || !data) {
            return (<FormLoader message="Connecting to WebSocket…"/>);
        }



        return (
            <>
                <FormControl>
                    <FormLabel id="demo-controlled-radio-buttons-group">Config Json</FormLabel>
                    <textarea  name="data" value={text} onChange={handleChange}></textarea>

                    <Button startIcon={<SaveIcon />}  color="primary" type="submit" onClick={saveChange}>
                        Save
                    </Button>
                </FormControl>
            </>
        );
    };

    return (
        <>
            <SectionContent title='Config Data' titleGutter>
                <Typography variant="body1" paragraph>
                    {content()}
                </Typography>
            </SectionContent>
        </>
    );
};

export default Config;
