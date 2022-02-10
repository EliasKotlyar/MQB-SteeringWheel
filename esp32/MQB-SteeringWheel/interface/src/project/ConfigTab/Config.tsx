import React, {FC, useEffect, useState} from 'react';

import {Button, Checkbox} from '@mui/material';
import SaveIcon from '@mui/icons-material/Save';

import {SectionContent, FormLoader, BlockFormControlLabel, ButtonRow, MessageBox} from '../../components';
import {updateValue, useRest} from '../../utils';

import * as DemoApi from '../api';
import {ConfigData, LightState} from '../types';


const Config: FC = () => {
    const {
        loadData, saveData, saving, setData, data, errorMessage
    } = useRest<ConfigData>({read: DemoApi.readConfig, update: DemoApi.updateConfig});

    const [textAreaText, setTextAreaText] = useState("");

    useEffect(() => {
        loadData().then(function (){
            const textData = JSON.stringify(data, null, 2);
            setTextAreaText(textData);
        });

    }, [loadData]);
    //const updateFormValue = updateValue(setData);

    const handleChange = (event: React.ChangeEvent<HTMLTextAreaElement>) => {
        setTextAreaText(event.target.value);
        /*


         */
    }
    const saveToServer = async (event:object) => {
        let configData: ConfigData = {
            mapping: JSON.parse(textAreaText)
            //mapping: {"test":"test"}
        };
        //setData(configData)
        //saveData(configData);
    }


    const content = () => {
        if (!data) {
            return (<FormLoader onRetry={loadData} errorMessage={errorMessage}/>);
        }


        return (
            <>
                <MessageBox
                    level="info"
                    message=""
                    my={2}
                />


                <textarea name="data" value={textAreaText} onChange={handleChange}></textarea>


                <ButtonRow mt={1}>
                    <Button startIcon={<SaveIcon/>} disabled={saving} variant="contained" color="primary" type="submit"
                            onClick={saveToServer}>
                        Save
                    </Button>
                </ButtonRow>
            </>
        );
    };

    return (
        <SectionContent title='REST Example' titleGutter>
            {content()}
        </SectionContent>
    );
};

export default Config;
